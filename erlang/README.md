# ruapu erlang binding

[![Hex pm](https://img.shields.io/hexpm/v/ruapu.svg)](https://hex.pm/packages/ruapu)
[![Docs](https://img.shields.io/badge/hex-docs-green.svg?style=flat)](https://hexdocs.pm/ruapu)

This is an Erlang/OTP binding for [ruapu](https://github.com/nihui/ruapu).

## Installation

To compile the module you simply run `rebar3 compile`.

To run the unit tests run `rebar3 eunit`.

To build the documentation run `rebar edoc`.

To use ruapu in your project you can just add it as a dependency in your rebar.config file in the following way:

```erlang
{deps, [
  {ruapu, "0.1.0"}
]}
```

### Usage

The getopt module provides two functions:

```erlang
ruapu:supports(ISA :: string() | atom() | binary()) -> boolean().

ruapu:rua() -> {ok, [string()]} | {error, string()}.
```

For example:

```erlang
% pass the ISA as a string, atom or binary
1> ruapu:supports("neon").
true
2> ruapu:supports(neon).
true
3> ruapu:supports(<<"neon">>).
true
% get all supported ISAs
4> ruapu:rua().
{ok,["neon","vfpv4","asimdrdm","asimdhp","asimddp",
     "asimdfhm","bf16","i8mm","pmull","crc32","aes","sha1",
     "sha2","sha3","sha512","amx"]}
```

### For developers
To release a new version of the library, you need to use the `release.sh` script. It will copy the `ruapu.h` to the `c_src` directory so that it can included in the released package.
