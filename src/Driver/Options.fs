namespace Marsh.Compiler.Driver

open Argu

type CliArgs =
    | [<MainCommand>] Input of string
    | Dump_Tokens
    | Version

    interface IArgParserTemplate with
        member this.Usage =
            match this with
            | Input _ -> "Input Source file."
            | Dump_Tokens -> "Print lexer tokens."
            | Version -> "Show Compiler version."
