#include <erl_nif.h>
#include <stdbool.h>
#include <stdint.h>
#define RUAPU_IMPLEMENTATION
#include "ruapu.h"

ERL_NIF_TERM atom(ErlNifEnv *env, const char *msg) {
  ERL_NIF_TERM a;
  if (enif_make_existing_atom(env, msg, &a, ERL_NIF_LATIN1)) {
    return a;
  } else {
    return enif_make_atom(env, msg);
  }
}

ERL_NIF_TERM error(ErlNifEnv *env, const char *msg) {
  ERL_NIF_TERM error_atom = atom(env, "error");
  ERL_NIF_TERM msg_term = enif_make_string(env, msg, ERL_NIF_LATIN1);
  return enif_make_tuple2(env, error_atom, msg_term);
}

ERL_NIF_TERM ok(ErlNifEnv *env) { return atom(env, "ok"); }

ERL_NIF_TERM ok_tuple(ErlNifEnv *env, ERL_NIF_TERM term) {
  return enif_make_tuple2(env, atom(env, "ok"), term);
}

const char *get_string(ErlNifEnv *env, ERL_NIF_TERM term) {
  char *result = NULL;
  unsigned len;
  int ret = enif_get_list_length(env, term, &len);

  if (ret) {
    result = (char *)enif_alloc(sizeof(char) * (len + 1));
    ret = enif_get_string(env, term, result, len + 1, ERL_NIF_LATIN1);
    if (ret > 0) {
      return result;
    } else {
      enif_free((void *)result);
      return NULL;
    }
  }

  ErlNifBinary bin;
  ret = enif_inspect_binary(env, term, &bin);
  if (ret) {
    result = (char *)enif_alloc(sizeof(char) * (bin.size + 1));
    if (result == NULL) {
      return NULL;
    }
    memcpy(result, bin.data, bin.size);
    result[bin.size] = '\0';
    return result;
  }

  ret = enif_get_atom_length(env, term, &len, ERL_NIF_LATIN1);
  if (ret) {
    result = (char *)enif_alloc(sizeof(char) * (len + 1));
    ret = enif_get_atom(env, term, result, len + 1, ERL_NIF_LATIN1);
    if (ret) {
      return result;
    } else {
      enif_free((void *)result);
      return NULL;
    }
  }

  return NULL;
}

static ERL_NIF_TERM nif_supports(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  const char *isa = get_string(env, argv[0]);
  if (isa == NULL) {
    return enif_make_badarg(env);
  }
  int supports = ruapu_supports(isa);
  enif_free((void *)isa);
  if (supports) {
    return atom(env, "true");
  } else {
    return atom(env, "false");
  }
}

static ERL_NIF_TERM nif_rua(ErlNifEnv *env, int argc,
                            const ERL_NIF_TERM argv[]) {
  const char *const *supported = ruapu_rua();
  const char *const *supported_start = supported;
  uint32_t count = 0;
  while (*supported_start) {
    supported_start++;
    count++;
  }
  if (count == 0) {
    ERL_NIF_TERM list = enif_make_list(env, 0, NULL);
    return ok_tuple(env, list);
  }

  ERL_NIF_TERM *terms =
      (ERL_NIF_TERM *)enif_alloc(sizeof(ERL_NIF_TERM) * count);
  if (terms == NULL) {
    return error(env, "enif_alloc failed");
  }
  supported_start = supported;
  for (uint32_t i = 0; i < count; i++) {
    terms[i] = enif_make_string(env, *supported_start, ERL_NIF_LATIN1);
    supported_start++;
  }

  ERL_NIF_TERM list = enif_make_list_from_array(env, terms, count);
  enif_free(terms);
  return ok_tuple(env, list);
}

static int on_load(ErlNifEnv *env, void **_sth1, ERL_NIF_TERM _sth2) {
  ruapu_init();
  return 0;
}

static int on_reload(ErlNifEnv *_sth0, void **_sth1, ERL_NIF_TERM _sth2) {
  return 0;
}

static int on_upgrade(ErlNifEnv *_sth0, void **_sth1, void **_sth2,
                      ERL_NIF_TERM _sth3) {
  return 0;
}

static ErlNifFunc nif_functions[] = {
    {"supports", 1, nif_supports, ERL_NIF_DIRTY_JOB_CPU_BOUND},
    {"rua", 0, nif_rua, ERL_NIF_DIRTY_JOB_CPU_BOUND},
};

ERL_NIF_INIT(ruapu_nif, nif_functions, on_load, on_reload, on_upgrade, NULL);
