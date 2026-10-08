namespace Marsh.Compiler.Frontend

open System
open System.Collections.Generic

module Lexer =
    let Tokenize (sourceName: string) (source: string) : Token List =
        //imperative Lexer will be prob better
        let tokens = ResizeArray<Token>()

        let keywords =
            dict["fun", TokenKind.KFun
                 "let", TokenKind.KLet
                 "mut", TokenKind.KMut]

        let mutable pos = 0
        // lineStart is the offset of the first char in the current line ;)
        let mutable line = 1
        let mutable lineStart = 0

        let addToken kind (start: int) =
            tokens.Add(
                {
                    Kind = kind
                    Value = source.Substring(start, pos - start)
                    Span =
                        {
                            Line = unativeint line
                            Column = unativeint (start - lineStart + 1)
                            Offset = unativeint start
                            Length = unativeint (pos - start)
                            SourceName = sourceName
                        }
                }
            )

        let symbol kind =
            let start = pos
            pos <- pos + 1
            addToken kind start

        while pos < source.Length do
            let c = source.[pos]

            match c with
            | ' '
            | '\t'
            | '\r' -> pos <- pos + 1
            | '\n' ->
                pos <- pos + 1
                line <- line + 1
                lineStart <- pos
            | '(' -> symbol TokenKind.LParen
            | ')' -> symbol TokenKind.RParen
            | '{' -> symbol TokenKind.LBrace
            | '}' -> symbol TokenKind.RBrace
            | ':' -> symbol TokenKind.Colon
            | c when Char.IsDigit c ->
                let start = pos

                while pos < source.Length && Char.IsDigit source.[pos] do
                    pos <- pos + 1

                addToken TokenKind.IntLiteral start
            | c when Char.IsLetter c ->
                let start = pos

                while pos < source.Length && Char.IsLetterOrDigit source.[pos] do
                    pos <- pos + 1

                let id = source.Substring(start, pos - start)

                if keywords.ContainsKey id then
                    addToken keywords[id] start
                else
                    addToken TokenKind.Identifiter start

            | _ -> pos <- pos + 1

        tokens
