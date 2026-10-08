//TODO: compiler workflow
namespace Marsh.Compiler.Driver

open System.IO
open Marsh.Compiler.Frontend

module Compiler =
    let compile (path: string) (dumpTokens: bool) : int =
        if not (File.Exists path) then
            eprintfn "error: File %s not found" path
            1
        else
            let source = File.ReadAllText path
            let tokens = Lexer.Tokenize path source

            if dumpTokens then
                for token in tokens do
                    printfn "%A" token

            0
