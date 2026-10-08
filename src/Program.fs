module Marsh.Compiler.Program

open Argu
open Marsh.Compiler.Driver

[<EntryPoint>]
let main argv =
    let parser = ArgumentParser.Create<CliArgs>(programName = "marshc")
    let args = parser.ParseCommandLine(argv, raiseOnUsage = false)

    if args.IsUsageRequested then
        printfn "%s" (parser.PrintUsage())
    elif args.Contains Version then
        printfn "marshc 0.1.0"

    0
