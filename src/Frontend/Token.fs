namespace Marsh.Compiler.Frontend

type TokenKind =
    | Identifiter
    //keywords
    | KFun
    //symbols
    | LParen
    | RParen
    | Colon
    | LBrace
    | RBrace
    // literals
    | IntLiteral

type SourceSpan =
    {
        Line: unativeint
        Column: unativeint
        Offset: unativeint
        Length: unativeint
        SourceName: string
    }

type Token =
    {
        Kind: TokenKind
        Value: string
        Span: SourceSpan
    }
