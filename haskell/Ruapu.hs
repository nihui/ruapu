{-# Language ForeignFunctionInterface #-}

module Ruapu where

import Foreign
import Foreign.C.String (CString, withCAString, peekCAString)

foreign import ccall "ruapu.c ruapu_init"
    init :: IO ()

foreign import ccall "ruapu.c ruapu_supports"
    cSupports :: CString -> IO Bool

foreign import ccall "ruapu.c ruapu_rua"
    cRua :: IO (Ptr CString)

supports :: String -> IO Bool
supports = flip withCAString cSupports

rua :: IO [String]
rua = cRua >>= peekArray0 nullPtr >>= mapM peekCAString
