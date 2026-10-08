namespace Marsh.Compiler.Driver

open Argu

type CliArgs =
    | Version

    interface IArgParserTemplate with
        member this.Usage =
            match this with
            | Version -> "Show Compiler version."
