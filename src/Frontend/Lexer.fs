namespace Marsh.Compiler.Frontend

open System
open System.Collections.Generic

module Lexer =
    let Tokenize (source: string) : Token List =
        //imperative Lexer will be prob better
        let tokens = ResizeArray<Token>()
        let keywords = dict["fun", TokenKind.KFun]
        let mutable pos = 0

        while pos < source.Length do
            let c = source.[pos]

            match c with
            | ' '
            | '\t'
            | '\r'
            | '\n' -> pos <- pos + 1
            | '(' ->
                tokens.Add(
                    {
                        Kind = TokenKind.LParen
                        Value = "("
                        Span =
                            {
                                Line = 0un //span setted to 0 for noow
                                Column = 0un
                                Offset = 0un
                                Length = 0un
                                SourceName = ""
                            }
                    }
                )

                pos <- pos + 1
            | ')' ->
                tokens.Add(
                    {
                        Kind = TokenKind.RParen
                        Value = "("
                        Span =
                            {
                                Line = 0un //span setted to 0 for noow
                                Column = 0un
                                Offset = 0un
                                Length = 0un
                                SourceName = ""
                            }
                    }
                )

                pos <- pos + 1
            | '{' ->
                tokens.Add(
                    {
                        Kind = TokenKind.LBrace
                        Value = "("
                        Span =
                            {
                                Line = 0un //span setted to 0 for noow
                                Column = 0un
                                Offset = 0un
                                Length = 0un
                                SourceName = ""
                            }
                    }
                )

                pos <- pos + 1
            | '}' ->
                tokens.Add(
                    {
                        Kind = TokenKind.RBrace
                        Value = "("
                        Span =
                            {
                                Line = 0un //span setted to 0 for noow
                                Column = 0un
                                Offset = 0un
                                Length = 0un
                                SourceName = ""
                            }
                    }
                )

                pos <- pos + 1
            | ':' ->
                tokens.Add(
                    {
                        Kind = TokenKind.Colon
                        Value = "("
                        Span =
                            {
                                Line = 0un //span setted to 0 for noow
                                Column = 0un
                                Offset = 0un
                                Length = 0un
                                SourceName = ""
                            }
                    }
                )

                pos <- pos + 1
            | c when Char.IsDigit c ->
                let start = pos

                while Char.IsDigit source.[pos] do
                    pos <- pos + 1

                let num = source.Substring(start, pos - start)

                tokens.Add(
                    {
                        Kind = TokenKind.IntLiteral
                        Value = num
                        Span =
                            {
                                Line = 0un
                                Column = 0un
                                Offset = 0un
                                Length = 0un
                                SourceName = ""
                            }
                    }
                )
            | c when Char.IsLetter c ->
                let start = pos

                while Char.IsLetterOrDigit source.[pos] do
                    pos <- pos + 1

                let id = source.Substring(start, pos - start)

                if keywords.ContainsKey id then
                    tokens.Add(
                        {
                            Kind = keywords[id]
                            Value = id
                            Span =
                                {
                                    Line = 0un
                                    Column = 0un
                                    Offset = 0un
                                    Length = 0un
                                    SourceName = ""
                                }
                        }
                    )
                else
                    tokens.Add(
                        {
                            Kind = TokenKind.Identifiter
                            Value = id
                            Span =
                                {
                                    Line = 0un
                                    Column = 0un
                                    Offset = 0un
                                    Length = 0un
                                    SourceName = ""
                                }
                        }
                    )


            | _ -> pos <- pos + 1

        tokens
