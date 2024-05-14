#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cwchar>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

enum TokenKind {
  EOL,
  Ident,
  CharLit,
  StringLit,
  Number,

  Var,
  Set,
  Inc,
  Dec,
  Add,
  Sub,
  Mul,
  DivMod,
  Div,
  Mod,
  Cmp,
  A2B,
  B2A,
  LSet,
  LGet,
  IfEq,
  IfNeq,
  WNeq,
  Proc,
  End,
  Call,
  Read,
  Msg,

  OpenSquare,
  CloseSquare,
};

struct Token {
  TokenKind kind;
  std::variant<int, std::string, char> value;

public:
  friend std::ostream &operator<<(std::ostream &s, const Token &token) {
    switch (token.kind) {
    case EOL:
      return s << "EOL";
    case Ident:
      return s << "Ident " << std::get<std::string>(token.value);
    case CharLit:
      return s << "CharLit " << std::get<char>(token.value);
    case StringLit:
      return s << "StringLit " << std::get<std::string>(token.value);
    case Number:
      return s << "Number " << std::get<int>(token.value);
    case Var:
      return s << "Var";
    case Set:
      return s << "Set";
    case Inc:
      return s << "Inc";
    case Dec:
      return s << "Dec";
    case Add:
      return s << "Add";
    case Sub:
      return s << "Sub";
    case Mul:
      return s << "Mul";
    case DivMod:
      return s << "DivMod";
    case Div:
      return s << "Div";
    case Mod:
      return s << "Mod";
    case Cmp:
      return s << "Cmp";
    case A2B:
      return s << "A2B";
    case B2A:
      return s << "B2A";
    case LSet:
      return s << "LSet";
    case LGet:
      return s << "LGet";
    case IfEq:
      return s << "IfEq";
    case IfNeq:
      return s << "IfNeq";
    case WNeq:
      return s << "WNeq";
    case Proc:
      return s << "Proc";
    case End:
      return s << "End";
    case Call:
      return s << "Call";
    case Read:
      return s << "Read";
    case Msg:
      return s << "Msg";
    default:
      return s << "Unknown";
    }
  }
};

void skip_whitespace(const std::string &source, size_t &i) {
  while (i < source.length())
    if (source[i] == ' ' || source[i] == '\t' || source[i] == '\r')
      i++;
    else
      return;
}

void skip_until_newline(const std::string &source, size_t &i) {
  while (i < source.length())
    if (source[i] == '\n')
      return;
    else
      i++;
}

std::string scan_while_in(const std::string &source, size_t &i,
                          const std::string &in) {
  std::string result;
  while (i < source.length()) {
    bool found = false;

    for (char c : in)
      if (source[i] == c) {
        found = true;
        break;
      }

    if (!found)
      break;
    result.push_back(source[i]);
    i++;
  }

  return result;
}

Token scan_char_lit(const std::string &source, size_t &i) {
  assert(source[i] == '\'');
  i++;

  char value = source[i];
  if (source[i] == '\\') {
    char c = source[++i];
    if (c == 'n')
      value = '\n';
    else if (c == 't')
      value = '\t';
    else if (c == 'r')
      value = '\r';
    else if (c == '\\')
      value = '\\';
    else if (c == '\'')
      value = '\'';
    else if (c == '\"')
      value = '\"';
    else
      assert(false);
  }

  i++;
  assert(source[i] == '\'');
  i++;
  return Token{.kind = CharLit, .value = value};
}

Token scan_string_lit(const std::string &source, size_t &i) {
  assert(source[i++] == '\"');
  std::string value;

  while (i < source.length() && source[i] != '\"') {
    if (source[i] == '\\') {
      assert(i + 1 < source.length());
      char c = source[++i];
      if (c == 'n')
        value.push_back('\n');
      else if (c == 't')
        value.push_back('\t');
      else if (c == 'r')
        value.push_back('\r');
      else if (c == '\\')
        value.push_back('\\');
      else if (c == '\'')
        value.push_back('\'');
      else if (c == '\"')
        value.push_back('\"');
      else
        assert(false);
    } else
      value.push_back(source[i]);
    i++;
  }

  assert(i < source.length() && source[i] == '\"');
  i++;
  return Token{.kind = StringLit, .value = value};
}

std::vector<Token> tokenize(const std::string &source) {
  std::vector<Token> result;

  size_t i = 0;
  while (i < source.length()) {
    skip_whitespace(source, i);

    if (i >= source.length())
      break;

    if (source[i] == '\n') {
      result.push_back(Token{.kind = EOL});
      i++;
      continue;
    }

    if (source[i] == '[') {
      result.push_back(Token{.kind = OpenSquare});
      i++;
      continue;
    }

    if (source[i] == ']') {
      result.push_back(Token{.kind = CloseSquare});
      i++;
      continue;
    }

    if (source.find("//", i) == i || source.find("--", i) == i ||
        source.find("#", i) == i) {
      skip_until_newline(source, i);
      continue;
    }

    if (source.find_first_of(
            "$_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", i) == i) {
      std::string word = scan_while_in(
          source, i,
          "$_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

      std::transform(word.begin(), word.end(), word.begin(),
                     [](unsigned char c) { return std::tolower(c); });

      if (word == "var")
        result.push_back(Token{.kind = Var});
      else if (word == "set")
        result.push_back(Token{.kind = Set});
      else if (word == "inc")
        result.push_back(Token{.kind = Inc});
      else if (word == "dec")
        result.push_back(Token{.kind = Dec});
      else if (word == "add")
        result.push_back(Token{.kind = Add});
      else if (word == "sub")
        result.push_back(Token{.kind = Sub});
      else if (word == "mul")
        result.push_back(Token{.kind = Mul});
      else if (word == "divmod")
        result.push_back(Token{.kind = DivMod});
      else if (word == "div")
        result.push_back(Token{.kind = Div});
      else if (word == "mod")
        result.push_back(Token{.kind = Mod});
      else if (word == "cmp")
        result.push_back(Token{.kind = Cmp});
      else if (word == "a2b")
        result.push_back(Token{.kind = A2B});
      else if (word == "b2a")
        result.push_back(Token{.kind = B2A});
      else if (word == "lset")
        result.push_back(Token{.kind = LSet});
      else if (word == "lget")
        result.push_back(Token{.kind = LGet});
      else if (word == "ifeq")
        result.push_back(Token{.kind = IfEq});
      else if (word == "ifneq")
        result.push_back(Token{.kind = IfNeq});
      else if (word == "wneq")
        result.push_back(Token{.kind = WNeq});
      else if (word == "proc")
        result.push_back(Token{.kind = Proc});
      else if (word == "end")
        result.push_back(Token{.kind = End});
      else if (word == "call")
        result.push_back(Token{.kind = Call});
      else if (word == "read")
        result.push_back(Token{.kind = Read});
      else if (word == "msg")
        result.push_back(Token{.kind = Msg});
      else if (word == "rem") {
        skip_until_newline(source, i);
        continue;
      } else
        result.push_back(Token{.kind = Ident, .value = word});

      continue;
    }

    if (source[i] == '\'') {
      result.push_back(scan_char_lit(source, i));
      continue;
    }

    if (source[i] == '\"') {
      result.push_back(scan_string_lit(source, i));
      continue;
    }

    if (source.find_first_of("-0123456789", i) == i) {
      bool negative = false;
      if (source[i] == '-') {
        negative = true;
        i++;
      }

      std::string lit = scan_while_in(source, i, "0123456789");
      int value = atoi(lit.c_str());
      if (negative)
        value *= -1;
      result.push_back(Token{.kind = Number, .value = value});
      continue;
    }

    assert(false);
  }

  return result;
}

struct ProcDetail {
  size_t token_idx;
  std::unordered_map<std::string, size_t>
      param_to_idx; // param name -> var index
};

void print_expr(const Token &token) {
  if (token.kind == Number)
    std::cerr << std::get<int>(token.value);
  else if (token.kind == StringLit)
    std::cerr << '"' << std::get<std::string>(token.value) << '"';
  else if (token.kind == CharLit)
    std::cerr << '\'' << std::get<char>(token.value) << '\'';
  else
    std::cerr << std::get<std::string>(token.value);
}

struct Context {
  std::string prog;
  std::unordered_map<std::string, size_t> variables; // var name -> var index
  std::unordered_map<std::string, ProcDetail> proc_maps; // proc name -> detail
  size_t total_variables;
  size_t last_pos;
};

void go_to(Context &ctx, size_t target) {
  if (ctx.last_pos == target)
    return;

  if (ctx.last_pos < target)
    for (size_t i = ctx.last_pos; i < target; i++)
      ctx.prog.push_back('>');
  else
    for (size_t i = target; i < ctx.last_pos; i++)
      ctx.prog.push_back('<');

  ctx.last_pos = target;
}

size_t alloc_temp(Context &ctx, size_t count) {
  size_t reg = ctx.total_variables;
  ctx.total_variables += count;
  return reg;
}

void dealloc_temp(Context &ctx, size_t count) { ctx.total_variables -= count; }

void emit_read(Context &ctx, const Token &target) {
  std::string varname = std::get<std::string>(target.value);
  size_t varidx = ctx.variables[varname];

  std::cerr << "read " << varname << std::endl;

  go_to(ctx, varidx);
  ctx.prog.push_back(',');
}

void add_value(Context &ctx, const int value) {
  if (value > 0)
    for (int i = 0; i < value; i++)
      ctx.prog.push_back('+');
  else
    for (int i = 0; i < -value; i++)
      ctx.prog.push_back('-');
}

// constraint: source != target
void emit_internal_move(Context &ctx, const size_t source, bool is_dec,
                        const size_t target) {
  go_to(ctx, source);
  ctx.prog += "[-";
  go_to(ctx, target);
  ctx.prog += is_dec ? "-" : "+";
  go_to(ctx, source);
  ctx.prog += "]";
}

void emit_internal_clear(Context &ctx, const size_t target) {
  go_to(ctx, target);
  ctx.prog += "[-]";
}

// set targetid <- varidx. varidx is leave unmodified.
void emit_internal_copy(Context &ctx, size_t varidx, size_t targetid) {
  if (varidx == targetid)
    return;
  emit_internal_clear(ctx, targetid);

  size_t t0 = alloc_temp(ctx, 1);
  emit_internal_clear(ctx, t0);

  go_to(ctx, varidx);
  ctx.prog += "[-";
  go_to(ctx, targetid);
  ctx.prog += "+";
  go_to(ctx, t0);
  ctx.prog += "+";
  go_to(ctx, varidx);
  ctx.prog += "]";
  emit_internal_move(ctx, t0, false, varidx);

  dealloc_temp(ctx, 1);
}

// set targetid <- value. value is leave unmodified.
void emit_internal_set(Context &ctx, const Token &value, size_t targetid) {

  if (value.kind == Number) {
    int v = std::get<int>(value.value);
    emit_internal_clear(ctx, targetid);
    go_to(ctx, targetid);
    add_value(ctx, v);
  } else if (value.kind == CharLit) {
    int v = (int)std::get<char>(value.value);
    emit_internal_clear(ctx, targetid);
    go_to(ctx, targetid);
    add_value(ctx, v);
  } else {
    std::string varname = std::get<std::string>(value.value);
    size_t varidx = ctx.variables[varname];
    emit_internal_copy(ctx, varidx, targetid);
  }
}

void emit_internal_while_consume_begin(Context &ctx, size_t varid) {
  go_to(ctx, varid);
  ctx.prog += "[";
}

void emit_internal_while_consume_end(Context &ctx, size_t varid) {
  go_to(ctx, varid);
  ctx.prog += "-]";
}

void emit_internal_a_eq_b(Context &ctx, size_t a, size_t b, size_t target) {
  size_t t0 = alloc_temp(ctx, 2);
  size_t t1 = t0 + 1;

  emit_internal_clear(ctx, target);
  go_to(ctx, target);
  ctx.prog += "+";
  emit_internal_copy(ctx, a, t0);
  emit_internal_copy(ctx, b, t1);
  emit_internal_move(ctx, t0, true, t1);
  go_to(ctx, t1);
  ctx.prog += "[[-]";
  go_to(ctx, target);
  ctx.prog += "-";
  go_to(ctx, t1);
  ctx.prog += "]";
  dealloc_temp(ctx, 2);
}

// constraint: target != a && target != b
void emit_internal_a_le_b(Context &ctx, size_t a, size_t b, size_t target) {
  size_t ta = alloc_temp(ctx, 4);
  size_t tb = ta + 1;
  size_t t0 = ta + 2;
  size_t t1 = ta + 3;

  emit_internal_clear(ctx, target);
  go_to(ctx, target);
  ctx.prog += "+";

  emit_internal_copy(ctx, a, ta);
  emit_internal_copy(ctx, b, tb);
  {
    emit_internal_while_consume_begin(ctx, ta);

    emit_internal_copy(ctx, tb, t1); // t1 = tb
    emit_internal_clear(ctx, t0);    // t0 = 1;
    go_to(ctx, t0);
    ctx.prog += "+";
    go_to(ctx, t1); // if t1: t0--;
    ctx.prog += "[[-]";
    go_to(ctx, t0);
    ctx.prog += "-";
    go_to(ctx, t1);
    ctx.prog += "]";
    // overall: t0 = tb == 0

    // if tb == 0: target--;
    go_to(ctx, t0);
    ctx.prog += "[[-]";
    go_to(ctx, target);
    ctx.prog += "-";
    go_to(ctx, t0);
    ctx.prog += "]";

    go_to(ctx, tb);
    ctx.prog += "-";
    emit_internal_while_consume_end(ctx, ta);
  }

  dealloc_temp(ctx, 4);
}

void emit_add(Context &ctx, const Token &a, const Token &b,
              const Token &target) {
  std::string targetvar = std::get<std::string>(target.value);
  size_t targetid = ctx.variables[targetvar];

  std::cerr << "add ";
  print_expr(a);
  std::cerr << " + ";
  print_expr(b);
  std::cerr << " -> " << targetvar << std::endl;

  size_t t0 = alloc_temp(ctx, 1);
  emit_internal_set(ctx, a, t0);
  emit_internal_set(ctx, b, targetid);
  emit_internal_move(ctx, t0, false, targetid);
  dealloc_temp(ctx, 1);
}

void emit_sub(Context &ctx, const Token &a, const Token &b,
              const Token &target) {
  std::string targetvar = std::get<std::string>(target.value);
  size_t targetid = ctx.variables[targetvar];

  std::cerr << "sub ";
  print_expr(a);
  std::cerr << " - ";
  print_expr(b);
  std::cerr << " -> " << targetvar << std::endl;

  size_t t0 = alloc_temp(ctx, 1);
  emit_internal_set(ctx, b, t0);
  emit_internal_set(ctx, a, targetid);
  emit_internal_move(ctx, t0, true, targetid);
  dealloc_temp(ctx, 1);
}

void emit_set(Context &ctx, const Token &target, const Token &value) {
  std::string targetname = std::get<std::string>(target.value);
  size_t targetidx = ctx.variables[targetname];

  std::cerr << "set " << targetname << " -> ";
  print_expr(value);
  std::cerr << std::endl;

  emit_internal_set(ctx, value, targetidx);
}

void emit_inc(Context &ctx, const Token &target, const Token &value) {
  std::string targetname = std::get<std::string>(target.value);
  size_t targetidx = ctx.variables[targetname];

  std::cerr << "inc " << targetname << " by ";
  print_expr(value);
  std::cerr << std::endl;

  size_t t0 = alloc_temp(ctx, 1);
  emit_internal_set(ctx, value, t0);
  emit_internal_move(ctx, t0, false, targetidx);
  dealloc_temp(ctx, 1);
}

void emit_dec(Context &ctx, const Token &target, const Token &value) {
  std::string targetname = std::get<std::string>(target.value);
  size_t targetidx = ctx.variables[targetname];

  std::cerr << "dec " << targetname << " by ";
  print_expr(value);
  std::cerr << std::endl;

  size_t t0 = alloc_temp(ctx, 1);
  emit_internal_set(ctx, value, t0);
  emit_internal_move(ctx, t0, true, targetidx);
  dealloc_temp(ctx, 1);
}

void emit_msg(Context &ctx, const std::vector<Token> msgs) {
  std::cerr << "print ";
  for (auto msg : msgs)
    print_expr(msg);
  std::cerr << std::endl;

  for (const Token &tok : msgs) {
    if (tok.kind == StringLit) {
      size_t temp0 = alloc_temp(ctx, 1);
      go_to(ctx, temp0);
      ctx.prog += "[-]";
      std::string value = std::get<std::string>(tok.value);
      int last = 0;
      for (char c : value) {
        add_value(ctx, (int)c - last);
        ctx.prog += ".";
        last = c;
      }
      dealloc_temp(ctx, 1);
    } else if (tok.kind == Ident) {
      std::string varname = std::get<std::string>(tok.value);
      size_t varid = ctx.variables[varname];
      go_to(ctx, varid);
      ctx.prog += ".";
    } else {
      assert(false);
    }
  }
}

void emit_mul(Context &ctx, const Token &a, const Token &b,
              const Token &target) {
  std::string targetvar = std::get<std::string>(target.value);
  size_t targetid = ctx.variables[targetvar];

  std::cerr << "mul ";
  print_expr(a);
  std::cerr << " * ";
  print_expr(b);
  std::cerr << " -> " << targetvar << std::endl;

  size_t t0 = alloc_temp(ctx, 3);
  size_t t1 = t0 + 1;
  size_t t2 = t0 + 2;
  emit_internal_set(ctx, a, t0);
  emit_internal_set(ctx, b, t1);
  emit_internal_clear(ctx, targetid);
  {
    emit_internal_while_consume_begin(ctx, t0);
    emit_internal_copy(ctx, t1, t2);
    emit_internal_move(ctx, t2, false, targetid);
    emit_internal_while_consume_end(ctx, t0);
  }

  dealloc_temp(ctx, 3);
}

void emit_divmod(Context &ctx, const Token &a, const Token &b,
                 const Token &quotient, const Token &remainder) {
  std::string qvar = std::get<std::string>(quotient.value);
  size_t qid = ctx.variables[qvar];

  std::string rvar = std::get<std::string>(remainder.value);
  size_t rid = ctx.variables[rvar];

  size_t ta = alloc_temp(ctx, 5);
  size_t tb = ta + 1;
  size_t tq = ta + 2;
  size_t t0 = ta + 3;
  size_t t1 = ta + 4;

  emit_internal_clear(ctx, tq);
  emit_internal_clear(ctx, rid);

  emit_internal_set(ctx, a, ta);
  emit_internal_set(ctx, b, tb);

  {
    // while tb <= ta begin
    emit_internal_a_le_b(ctx, tb, ta, t1);
    go_to(ctx, t1);
    ctx.prog += "[";

    // ta -= tb
    emit_internal_copy(ctx, tb, t0);
    emit_internal_move(ctx, t0, true, ta);

    go_to(ctx, tq);
    ctx.prog += "+";

    // while end
    emit_internal_a_le_b(ctx, tb, ta, t1);
    go_to(ctx, t1);
    ctx.prog += "]";
  }
  emit_internal_copy(ctx, ta, rid);
  emit_internal_copy(ctx, tq, qid);

  dealloc_temp(ctx, 5);
}

void emit_div(Context &ctx, const Token &a, const Token &b,
              const Token &quotient) {
  std::string qvar = std::get<std::string>(quotient.value);
  size_t qid = ctx.variables[qvar];

  size_t ta = alloc_temp(ctx, 5);
  size_t tb = ta + 1;
  size_t tq = ta + 2;
  size_t t0 = ta + 3;
  size_t t1 = ta + 4;

  emit_internal_clear(ctx, tq);

  emit_internal_set(ctx, a, ta);
  emit_internal_set(ctx, b, tb);

  {
    // while tb <= ta begin
    emit_internal_a_le_b(ctx, tb, ta, t1);
    go_to(ctx, t1);
    ctx.prog += "[";

    // ta -= tb
    emit_internal_copy(ctx, tb, t0);
    emit_internal_move(ctx, t0, true, ta);

    go_to(ctx, tq);
    ctx.prog += "+";

    // while end
    emit_internal_a_le_b(ctx, tb, ta, t1);
    go_to(ctx, t1);
    ctx.prog += "]";
  }
  emit_internal_copy(ctx, tq, qid);

  dealloc_temp(ctx, 5);
}

void emit_mod(Context &ctx, const Token &a, const Token &b,
              const Token &remainder) {
  std::string rvar = std::get<std::string>(remainder.value);
  size_t rid = ctx.variables[rvar];

  size_t ta = alloc_temp(ctx, 5);
  size_t tb = ta + 1;
  size_t tq = ta + 2;
  size_t t0 = ta + 3;
  size_t t1 = ta + 4;

  emit_internal_clear(ctx, tq);
  emit_internal_clear(ctx, rid);

  emit_internal_set(ctx, a, ta);
  emit_internal_set(ctx, b, tb);

  {
    // while tb <= ta begin
    emit_internal_a_le_b(ctx, tb, ta, t1);
    go_to(ctx, t1);
    ctx.prog += "[";

    // ta -= tb
    emit_internal_copy(ctx, tb, t0);
    emit_internal_move(ctx, t0, true, ta);

    go_to(ctx, tq);
    ctx.prog += "+";

    // while end
    emit_internal_a_le_b(ctx, tb, ta, t1);
    go_to(ctx, t1);
    ctx.prog += "]";
  }
  emit_internal_copy(ctx, ta, rid);

  dealloc_temp(ctx, 5);
}

void emit_cmp(Context &ctx, const Token &a, const Token &b,
              const Token &target) {
  std::string varname = std::get<std::string>(target.value);
  size_t targetid = ctx.variables[varname];

  size_t ta = alloc_temp(ctx, 5);
  size_t tb = ta + 1;
  size_t t0 = ta + 2;
  size_t t1 = ta + 3;
  size_t tr = ta + 4;

  emit_internal_set(ctx, a, ta);
  emit_internal_set(ctx, b, tb);

  emit_internal_clear(ctx, tr);
  go_to(ctx, tr);
  ctx.prog += "+";

  {
    // if a <= b
    emit_internal_a_le_b(ctx, ta, tb, t0);
    go_to(ctx, t0);
    ctx.prog += "[[-]";

    // tr -= 2
    go_to(ctx, tr);
    add_value(ctx, -2);

    {
      // if ta == tb
      emit_internal_a_eq_b(ctx, ta, tb, t1);
      go_to(ctx, t1);
      ctx.prog += "[[-]";

      // tr = 0;
      emit_internal_clear(ctx, tr);

      go_to(ctx, t1);
      ctx.prog += "]";
    }

    go_to(ctx, t0);
    ctx.prog += "]";
  }
  emit_internal_copy(ctx, tr, targetid);

  dealloc_temp(ctx, 5);
}

std::string kcuf(const std::string &code) {
  std::vector<Token> tokens = tokenize(code);

  std::cerr << "Tokens" << std::endl;
  for (auto token : tokens)
    std::cerr << token << std::endl;
  std::cerr << "========================================================"
            << std::endl;

  size_t last_used_var_id = 0;
  std::unordered_map<std::string, size_t> variables; // var name -> var index
  std::unordered_map<std::string, ProcDetail> proc_maps; // proc name -> detail

  for (size_t i = 0; i < tokens.size(); i++)
    if (tokens[i].kind == Var)
      for (i = i + 1; i < tokens.size() && tokens[i].kind != EOL; i++) {
        variables[std::get<std::string>(tokens[i].value)] = last_used_var_id++;
        if (tokens[i + 1].kind == OpenSquare) {
          int size = std::get<int>(tokens[i + 2].value);
          i += 3;
          last_used_var_id += size - 1;
        }
      }

  for (size_t i = 0; i < tokens.size(); i++)
    if (tokens[i].kind == Proc) {
      proc_maps[std::get<std::string>(tokens[i + 1].value)] =
          ProcDetail{.token_idx = i};

      // std::unordered_map<std::string, size_t> param_to_idx;
      // for (size_t j = i + 1; j < tokens.size() && tokens[j].kind != EOL; j++)
      //   param_to_idx[std::get<std::string>(tokens[j].value)] =
      //       last_used_var_id++;
    }

  Context context = Context{.prog = std::string(),
                            .variables = std::move(variables),
                            .proc_maps = std::move(proc_maps),
                            .total_variables = last_used_var_id,
                            .last_pos = 0};

  for (size_t i = 0; i < tokens.size(); i++) {
    switch (tokens[i].kind) {
    case Var:
      while (i < tokens.size() && tokens[i].kind != EOL)
        i++;
      break;
    case Set:
      emit_set(context, tokens[i + 1], tokens[i + 2]);
      i += 3;
      break;

    case Inc:
      emit_inc(context, tokens[i + 1], tokens[i + 2]);
      i += 3;
      break;
    case Dec:
      emit_dec(context, tokens[i + 1], tokens[i + 2]);
      i += 3;
      break;

    case Add:
      emit_add(context, tokens[i + 1], tokens[i + 2], tokens[i + 3]);
      i += 4;
      break;
    case Sub:
      emit_sub(context, tokens[i + 1], tokens[i + 2], tokens[i + 3]);
      i += 4;
      break;
    case Mul:
      emit_mul(context, tokens[i + 1], tokens[i + 2], tokens[i + 3]);
      i += 4;
      break;
    case DivMod:
      emit_divmod(context, tokens[i + 1], tokens[i + 2], tokens[i + 3],
                  tokens[i + 4]);
      i += 5;
      break;
    case Div:
      emit_div(context, tokens[i + 1], tokens[i + 2], tokens[i + 3]);
      i += 4;
      break;
    case Mod:
      emit_mod(context, tokens[i + 1], tokens[i + 2], tokens[i + 3]);
      i += 4;
      break;

    case Cmp:
      emit_cmp(context, tokens[i + 1], tokens[i + 2], tokens[i + 3]);
      i += 4;
      break;

    case A2B:
    case B2A:

    case LSet:
    case LGet:

    case IfEq:
    case IfNeq:
    case WNeq:
    case Proc:
    case Call:
      assert(false);
      break;

    case Read:
      emit_read(context, tokens[i + 1]);
      i += 2;
      break;
    case Msg: {
      int start = ++i;
      while (i < tokens.size() && tokens[i].kind != EOL)
        i++;
      emit_msg(context,
               std::vector(tokens.begin() + start, tokens.begin() + i));
    } break;
    default:
      assert(false);
      break;
    }

    context.prog.push_back('\n');
  }

  return context.prog;
}

int main() {
  /*
   std::string result = solve("var q w e\n\
   read q\n\
   read w\n\
   add q w e\n\
   msg q \" \" w \" \" e\n\
   ");
  */

  /*
  std::string result = kcuf("var X//This is a comment\n\
read X--This is also a comment\n\
msg \"Bye\" X#No doubt it is a comment\n\
rem &&Some comment~!@#$\":<");
  */

  /*
  std::string result = kcuf("var A B\n\
sEt A 'a'\n\
msg a B\n\
set B 50\n\
msG A b\n\
inc A 10\n\
dec B -20\n\
msg A B");
   */

  /*
  std::string result = kcuf("var A B C\n\
read A\n\
read B\n\
add a b c\n\
msg a b c\n\
sub a b a\n\
msg a b c\n\
mul b a c\n\
msg a b c");
   */

  /*
  std::string result = kcuf("var A B C D\n\
set A 79\n\
set B 13\n\
msg A B C D\n\
divmod A B C D\n\
msg A B C D"); // expected: [79,13,6,1]
  */

  /*
  std::string result = kcuf("var A B C D\n\
set A 79\n\
set B 13\n\
divmod A B C D\n\
msg A B C D\n\
div C D C\n\
msg A B C D\n\
mod A D A\n\
msg A B C D"); // expected: [79,13,6,1,79,13,6,1,0,13,6,1]
  */

  std::string result = kcuf("var X K\n\
read X\n\
cmp 80 X K\n\
msg X K\n\
cmp X 'z' K\n\
msg X K\n\
cmp X X K\n\
msg X K");

  std::cerr << "Result:" << std::endl;
  std::cout << result << std::endl;

  std::cerr << "Evaluating" << std::endl;

  std::vector<uint8_t> memory(100, 0);
  size_t pos = 0;

  std::stack<size_t> s;
  std::unordered_map<size_t, size_t> start_to_end;
  std::unordered_map<size_t, size_t> end_to_start;
  for (size_t i = 0; i < result.length(); i++) {
    if (result[i] == '[')
      s.push(i);
    else if (result[i] == ']') {
      size_t start = s.top();
      s.pop();
      start_to_end[start] = i;
      end_to_start[i] = start;
    }
  }

  std::vector<uint8_t> input;
  input.push_back((uint8_t)128);

  for (size_t i = 0; i < result.length(); i++) {
    char c = result[i];
    switch (c) {
    case '>':
      pos++;
      break;
    case '<':
      pos--;
      break;
    case '+':
      memory[pos]++;
      break;
    case '-':
      memory[pos]--;
      break;
    case '[':
      if (!memory[pos])
        i = start_to_end[i];
      break;
    case ']':
      i = end_to_start[i] - 1;
      break;
    case '.':
      std::cerr << (int)memory[pos] << " ";
      break;
    case ',':
      memory[pos] = input.front();
      input.erase(input.begin());
      break;
    }
  }
  std::cerr << std::endl;
}
