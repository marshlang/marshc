module Marsh.Compiler.Program

open Argu
open Marsh.Compiler.Driver

[<EntryPoint>]
let main argv =
    let parser = ArgumentParser.Create<CliArgs>(programName = "marshc")
    let args = parser.ParseCommandLine(argv)

    if args.Contains Version then
        printfn "marshc 0.1.0"

    0
