module Marsh.Compiler.Program

open Argu
open Marsh.Compiler.Driver

[<EntryPoint>]
let main argv =
    let parser = ArgumentParser.Create<CliArgs>(programName = "marshc")
    let args = parser.ParseCommandLine(argv, raiseOnUsage = false)

    if args.IsUsageRequested then
        printfn "%s" (parser.PrintUsage())
        0
    elif args.Contains Version then
        printfn "marshc 0.1.0"
        0
    else
        match args.TryGetResult Input with
        | Some path ->
            let dumpTokens = args.Contains Dump_Tokens
            Compiler.compile path dumpTokens
        | None ->
            eprintfn "error: no input file provided"
            eprintfn "%s" (parser.PrintUsage())
            1
