-module(ruapu).
-export([rua/0, supports/1]).

-ifdef(TEST).
-include_lib("eunit/include/eunit.hrl").
-endif.

%% @doc
%%
%% Get a list of supported features.
-spec rua() -> {ok, [string()]} | {error, string()}.
rua() ->
    ruapu_nif:rua().

%% @doc
%%
%% Check if a feature is supported.
-spec supports(atom() | string() | binary()) -> boolean().
supports(ISA) ->
    ruapu_nif:supports(ISA).

-ifdef(EUNIT).
rua_test() ->
    ?assertMatch({ok, _}, rua()).

supports_test() ->
    ?assert(supports(<<"binary_non_exists_feature">>) =:= false),
    ?assert(supports("string_non_exists_feature") =:= false),
    ?assert(supports(atom_non_exists_feature) =:= false),
    {ok, Features} = rua(),
    ?assert(lists:all(fun(Feature) -> supports(Feature) end, Features)).
-endif.
