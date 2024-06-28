import re
from collections import namedtuple

Tok = namedtuple('Tok', 'name value')
OpInfo = namedtuple('OpInfo', 'prec assoc')

# Definición de OPINFO_MAP para operadores binarios
OPINFO_MAP = {
    '+': OpInfo(1, 'LEFT'),
    '-': OpInfo(1, 'LEFT'),
    '*': OpInfo(2, 'LEFT'),
    '/': OpInfo(2, 'LEFT'),
    '^': OpInfo(3, 'RIGHT'),
}

class Tokenizer(object):
    TOKPATTERN = re.compile("\s*(?:(\d+)|(.))")

    def __init__(self, source):
        self._tokgen = self._gen_tokens(source)
        self.cur_token = None
        self.get_next_token()

    def get_next_token(self):
        try:
            self.cur_token = next(self._tokgen)
        except StopIteration:
            self.cur_token = None
        return self.cur_token

    def _gen_tokens(self, source):
        for number, operator in self.TOKPATTERN.findall(source):
            if number:
                yield Tok('NUMBER', number)
            elif operator == '(':
                yield Tok('LEFTPAREN', '(')
            elif operator == ')':
                yield Tok('RIGHTPAREN', ')')
            else:
                yield Tok('BINOP', operator)

class ASTNode:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

    def __repr__(self):
        if self.left is not None or self.right is not None:
            return f"({self.value} {self.left} {self.right})"
        return f"{self.value}"

def compute_atom(tokenizer):
    tok = tokenizer.cur_token
    if tok.name == 'LEFTPAREN':
        tokenizer.get_next_token()
        val = compute_expr(tokenizer, 1)
        if tokenizer.cur_token.name != 'RIGHTPAREN':
            parse_error('unmatched "("')
        tokenizer.get_next_token()
        return val
    elif tok is None:
        parse_error('source ended unexpectedly')
    elif tok.name == 'BINOP':
        parse_error('expected an atom, not an operator "%s"' % tok.value)
    else:
        assert tok.name == 'NUMBER'
        tokenizer.get_next_token()
        return ASTNode(tok.value)

def compute_expr(tokenizer, min_prec):
    atom_lhs = compute_atom(tokenizer)

    while True:
        cur = tokenizer.cur_token
        if (cur is None or cur.name != 'BINOP' or OPINFO_MAP[cur.value].prec < min_prec):
            break

        op = cur.value
        prec, assoc = OPINFO_MAP[op]
        next_min_prec = prec + 1 if assoc == 'LEFT' else prec

        tokenizer.get_next_token()
        atom_rhs = compute_expr(tokenizer, next_min_prec)

        atom_lhs = ASTNode(op, atom_lhs, atom_rhs)

    return atom_lhs

# El resto del código permanece igual 

def compute_op(op, lhs, rhs):
    lhs = int(lhs); rhs = int(rhs)
    if op == '+':
        return lhs + rhs
    elif op == '-':
        return lhs - rhs
    elif op == '*':
        return lhs * rhs
    elif op == '/':
        return lhs / rhs
    elif op == '^':
        return lhs ** rhs
    else:
        parse_error('unknown operator "%s"' % op)

def parse_error(message):
    raise Exception(message)

# Ejemplo de uso
source = "2 + 4"
tokenizer = Tokenizer(source)
result = compute_expr(tokenizer, 1)
print(f"Resultado: {result}")