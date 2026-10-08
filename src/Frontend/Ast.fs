namespace Marsh.Compiler.Frontend


type Expr = ConstInt of nativeint //in the future there should be also ConstUInt


type Stmts = Expr

type FunctionNode = { name: string; body: Stmts }
