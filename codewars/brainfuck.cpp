#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cwchar>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

const std::string error_msg = "An error occured";

void assert_throw(bool v) {
  if (!v)
    throw error_msg;
}

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
  if (source[i] != '\'')
    throw "missing closing colon";
  i++;
  return Token{.kind = CharLit, .value = value};
}

Token scan_string_lit(const std::string &source, size_t &i) {
  assert(source[i++] == '\"');
  std::string value;

  while (i < source.length() && source[i] != '\"' && source[i] != EOL) {
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
        throw "invalid escape";
    } else
      value.push_back(source[i]);
    i++;
  }

  if (!(i < source.length() && source[i] == '\"'))
    throw "missing end of string";
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
  size_t token_idx, end_idx;
  std::vector<std::string> params;
};

struct BlockEndInstr {
  bool is_call;
  std::string function_name;
  size_t next_pc;

  size_t initial_pos, final_pos;
  size_t variables;
  std::string cleanup;
};

struct VarDetail {
  size_t id;
  bool is_list;
};

struct Context {
  std::string prog;
  std::unordered_map<std::string, std::stack<VarDetail>>
      variables; // var name -> var index
  std::unordered_map<std::string, ProcDetail> proc_maps; // proc name -> detail
  std::stack<BlockEndInstr> ends;
  std::unordered_set<std::string> called_procs;
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

size_t get_var(Context &ctx, std::string &name) {
  if (ctx.variables[name].empty())
    throw error_msg;
  return ctx.variables[name].top().id;
}

size_t get_non_list_var(Context &ctx, std::string &name) {
  if (ctx.variables[name].empty())
    throw error_msg;
  VarDetail detail = ctx.variables[name].top();
  if (detail.is_list)
    throw "var is a list";
  return detail.id;
}

VarDetail get_var_detail(Context &ctx, std::string &name) {
  if (ctx.variables[name].empty())
    throw error_msg;
  return ctx.variables[name].top();
}

void emit_read(Context &ctx, const Token &target) {
  std::string varname = std::get<std::string>(target.value);
  size_t varidx = get_var(ctx, varname);

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
    size_t varidx = get_var(ctx, varname);
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

void emit_internal_a_neq_b(Context &ctx, size_t a, size_t b, size_t target) {
  size_t t0 = alloc_temp(ctx, 2);
  size_t t1 = t0 + 1;

  emit_internal_a_eq_b(ctx, a, b, t0);
  emit_internal_clear(ctx, t1);
  go_to(ctx, t0);
  ctx.prog += "[";
  go_to(ctx, t1);
  add_value(ctx, 1);
  emit_internal_clear(ctx, t0);
  ctx.prog += "]+";
  go_to(ctx, t1);
  ctx.prog += "[";
  go_to(ctx, t0);
  add_value(ctx, -1);
  go_to(ctx, t1);
  add_value(ctx, -1);
  ctx.prog += "]";
  emit_internal_copy(ctx, t0, target);

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
  size_t targetid = get_var(ctx, targetvar);

  size_t t0 = alloc_temp(ctx, 1);
  emit_internal_set(ctx, a, t0);
  emit_internal_set(ctx, b, targetid);
  emit_internal_move(ctx, t0, false, targetid);
  dealloc_temp(ctx, 1);
}

void emit_sub(Context &ctx, const Token &a, const Token &b,
              const Token &target) {
  std::string targetvar = std::get<std::string>(target.value);
  size_t targetid = get_var(ctx, targetvar);

  size_t t0 = alloc_temp(ctx, 1);
  emit_internal_set(ctx, b, t0);
  emit_internal_set(ctx, a, targetid);
  emit_internal_move(ctx, t0, true, targetid);
  dealloc_temp(ctx, 1);
}

void emit_set(Context &ctx, const Token &target, const Token &value) {
  std::string targetname = std::get<std::string>(target.value);
  size_t targetidx = get_var(ctx, targetname);

  emit_internal_set(ctx, value, targetidx);
}

void emit_inc(Context &ctx, const Token &target, const Token &value) {
  std::string targetname = std::get<std::string>(target.value);
  size_t targetidx = get_var(ctx, targetname);

  size_t t0 = alloc_temp(ctx, 1);
  emit_internal_set(ctx, value, t0);
  emit_internal_move(ctx, t0, false, targetidx);
  dealloc_temp(ctx, 1);
}

void emit_dec(Context &ctx, const Token &target, const Token &value) {
  std::string targetname = std::get<std::string>(target.value);
  size_t targetidx = get_var(ctx, targetname);

  size_t t0 = alloc_temp(ctx, 1);
  emit_internal_set(ctx, value, t0);
  emit_internal_move(ctx, t0, true, targetidx);
  dealloc_temp(ctx, 1);
}

void emit_msg(Context &ctx, const std::vector<Token> msgs) {
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
      size_t varid = get_var(ctx, varname);
      go_to(ctx, varid);
      ctx.prog += ".";
    } else {
      assert(false);
    }
  }
}

// constrant: targetid != a && targetid != b. a and b will be modified
void emit_internal_mul(Context &ctx, const size_t a, const size_t b,
                       const size_t targetid) {
  size_t t0 = alloc_temp(ctx, 1);

  emit_internal_clear(ctx, targetid);
  {
    emit_internal_while_consume_begin(ctx, a);
    emit_internal_copy(ctx, b, t0);
    emit_internal_move(ctx, t0, false, targetid);
    emit_internal_while_consume_end(ctx, a);
  }

  dealloc_temp(ctx, 1);
}

void emit_mul(Context &ctx, const Token &a, const Token &b,
              const Token &target) {
  std::string targetvar = std::get<std::string>(target.value);
  size_t targetid = get_var(ctx, targetvar);

  size_t t0 = alloc_temp(ctx, 2);
  size_t t1 = t0 + 1;
  emit_internal_set(ctx, a, t0);
  emit_internal_set(ctx, b, t1);
  emit_internal_mul(ctx, t0, t1, targetid);
  dealloc_temp(ctx, 2);
}

// constraint a and b modified. all vars are unique
void emit_internal_divmod(Context &ctx, const size_t a, const size_t b,
                          const size_t q, const size_t rem) {
  size_t t0 = alloc_temp(ctx, 2);
  size_t t1 = t0 + 1;

  emit_internal_clear(ctx, q);
  emit_internal_clear(ctx, rem);

  {
    // while tb <= ta begin
    emit_internal_a_le_b(ctx, b, a, t1);
    go_to(ctx, t1);
    ctx.prog += "[";

    // ta -= tb
    emit_internal_copy(ctx, b, t0);
    emit_internal_move(ctx, t0, true, a);

    go_to(ctx, q);
    ctx.prog += "+";

    // while end
    emit_internal_a_le_b(ctx, b, a, t1);
    go_to(ctx, t1);
    ctx.prog += "]";
  }
  emit_internal_copy(ctx, a, rem);

  dealloc_temp(ctx, 2);
}

void emit_divmod(Context &ctx, const Token &a, const Token &b,
                 const Token &quotient, const Token &remainder) {
  std::string qvar = std::get<std::string>(quotient.value);
  size_t qid = get_var(ctx, qvar);

  std::string rvar = std::get<std::string>(remainder.value);
  size_t rid = get_var(ctx, rvar);

  size_t ta = alloc_temp(ctx, 4);
  size_t tb = ta + 1;
  size_t tq = ta + 2;
  size_t trem = ta + 3;
  emit_internal_set(ctx, a, ta);
  emit_internal_set(ctx, b, tb);
  emit_internal_divmod(ctx, ta, tb, tq, trem);
  emit_internal_copy(ctx, trem, rid);
  emit_internal_copy(ctx, tq, qid);
  dealloc_temp(ctx, 4);
}

void emit_div(Context &ctx, const Token &a, const Token &b,
              const Token &quotient) {
  std::string qvar = std::get<std::string>(quotient.value);
  size_t qid = get_var(ctx, qvar);

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
  size_t rid = get_var(ctx, rvar);

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
  size_t targetid = get_var(ctx, varname);

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

void emit_a2b(Context &ctx, const Token &a, const Token &b, const Token &c,
              const Token &target) {
  std::string varname = std::get<std::string>(target.value);
  size_t targetid = get_non_list_var(ctx, varname);

  size_t ta = alloc_temp(ctx, 6);
  size_t tb = ta + 1;
  size_t tc = ta + 2;
  size_t td = ta + 3;
  size_t tpow = ta + 4;
  size_t tx = ta + 5;

  emit_internal_set(ctx, a, ta);
  emit_internal_set(ctx, b, tb);
  emit_internal_set(ctx, c, tc);
  emit_internal_clear(ctx, td);

  // ta -= 48
  go_to(ctx, ta);
  add_value(ctx, -48);
  // tb -= 48
  go_to(ctx, tb);
  add_value(ctx, -48);
  // tc -= 48
  go_to(ctx, tc);
  add_value(ctx, -48);

  // td += tc
  emit_internal_move(ctx, tc, false, td);

  // tpow = 10
  emit_internal_clear(ctx, tpow);
  go_to(ctx, tpow);
  add_value(ctx, 10);

  // tx = tpow * tb
  emit_internal_mul(ctx, tb, tpow, tx);
  // td += tx
  emit_internal_move(ctx, tx, false, td);

  // tpow = 100
  emit_internal_clear(ctx, tpow);
  go_to(ctx, tpow);
  add_value(ctx, 100);

  // tx = tpow * ta
  emit_internal_mul(ctx, ta, tpow, tx);
  // td += tx
  emit_internal_move(ctx, tx, false, td);

  emit_internal_copy(ctx, td, targetid);
  dealloc_temp(ctx, 6);
}

void emit_b2a(Context &ctx, const Token &a, const Token &b, const Token &c,
              const Token &d) {
  std::string varname = std::get<std::string>(b.value);
  size_t bid = get_non_list_var(ctx, varname);

  varname = std::get<std::string>(c.value);
  size_t cid = get_non_list_var(ctx, varname);

  varname = std::get<std::string>(d.value);
  size_t did = get_non_list_var(ctx, varname);

  size_t ta = alloc_temp(ctx, 4);
  size_t t10 = ta + 1;
  size_t rem = ta + 2;
  size_t div = ta + 3;

  // t10 = 10
  emit_internal_clear(ctx, t10);
  go_to(ctx, t10);
  add_value(ctx, 10);

  // ta = a
  emit_internal_set(ctx, a, ta);

  // div, rem = a /% 10
  emit_internal_divmod(ctx, ta, t10, div, rem);
  // d = rem
  emit_internal_copy(ctx, rem, did);
  go_to(ctx, did);
  add_value(ctx, 48);

  // ta = div
  emit_internal_copy(ctx, div, ta);
  // t10 = 10
  emit_internal_clear(ctx, t10);
  go_to(ctx, t10);
  add_value(ctx, 10);
  // div, rem = a /% 10
  emit_internal_divmod(ctx, ta, t10, div, rem);
  // c = rem
  emit_internal_copy(ctx, rem, cid);
  go_to(ctx, cid);
  add_value(ctx, 48);
  // b = div
  emit_internal_copy(ctx, div, bid);
  go_to(ctx, bid);
  add_value(ctx, 48);

  dealloc_temp(ctx, 4);
}

// go right as much as current cell's value
void go_to_index(Context &ctx, const std::function<void()> f) {
  size_t ta = alloc_temp(ctx, 256);
  size_t offset = ta - ctx.last_pos;

  emit_internal_copy(ctx, ctx.last_pos, ta);
  go_to(ctx, ta);
  ctx.prog += "[[->+<]>-]";
  for (size_t i = 0; i < offset; i++)
    ctx.prog += '<';
  ctx.last_pos = ta;

  f();

  go_to(ctx, ta);

  dealloc_temp(ctx, 256);
}

std::string left_until_one = "+[<[>-]>[-<+>]<]<";
std::string right_until_one = "+[>[<-]<[->+<]>]>";

void emit_lset(Context &ctx, const Token &a, const Token &b, const Token &c) {
  std::string varname = std::get<std::string>(a.value);
  VarDetail a_var = get_var_detail(ctx, varname);
  if (!a_var.is_list)
    throw "not a list";
  size_t aid = a_var.id;

  if (c.kind == Ident) {
    std::string varname = std::get<std::string>(c.value);
    VarDetail var = get_var_detail(ctx, varname);
    if (var.is_list)
      throw "cannot insert list to list";
  }

  size_t tb = alloc_temp(ctx, 4);
  size_t tc = tb + 1;
  size_t tfence1 = tb + 2;
  size_t tfence0 = tb + 3;

  //                            v -> copied tc
  // tb|tc|tf| 0|ti|..|..|..|**| 0|tf|tc
  //       ^ tfence          ^ tfence

  // tb = b; tc = c;

  emit_internal_set(ctx, b, tb);
  emit_internal_set(ctx, c, tc);

  // set tfence1 = 1, tfence0 = 0
  emit_internal_clear(ctx, tfence0);
  emit_internal_clear(ctx, tfence1);
  go_to(ctx, tfence1);
  add_value(ctx, 1);

  size_t ti = alloc_temp(ctx, 1);

  size_t offset = ti - aid;
  emit_internal_copy(ctx, tb, ti);

  alloc_temp(ctx, 255 + 1 + 1 + 1);

  go_to(ctx, ti);
  ctx.prog += ">";
  for (int i = 0; i < 256 + 1 + 1; i++)
    ctx.prog += "[-]>";
  for (int i = 0; i < 256 + 1 + 1 + 1; i++)
    ctx.prog += "<";

  ctx.prog += "[[->+<]>-]"; // go right tb times
  ctx.prog += ">>+<<";      // add fencing after the index

  ctx.prog += left_until_one; // go left until found 1 (the left fence)
  ctx.prog += "<";            // then go one more left to go to tc
  {                           // while tc > 0
    ctx.prog += "[";
    ctx.prog += "->>>";          // dec tc, then go to ti
    ctx.prog += right_until_one; // go right until found 1 (the right fence)
    ctx.prog += ">+<<<";         // inc one cell after ith fence, then go to ti
    ctx.prog += left_until_one;  // go left until found 1 (the left fence)
    ctx.prog += "<";             // then go one more left to go to tc
    ctx.prog += "]";
  }
  ctx.prog += ">>>"; // move to ti
  ctx.prog +=
      right_until_one + ">"; // go right until found 1 (the right fence), then
                             // go one more right to get copied tc

  { // while the copied_tc > 0
    ctx.prog += "[";

    ctx.prog += "-";
    ctx.prog += "<<<";
    for (size_t i = 0; i < offset; i++)
      ctx.prog += '<';
    ctx.prog += "+";
    for (size_t i = 0; i < offset; i++)
      ctx.prog += '>';
    ctx.prog += ">>>";
    ctx.prog += "]";
  }

  ctx.prog += "<<<";
  ctx.prog += left_until_one; // go left until found 1 (the left fence)
  ctx.last_pos = tfence1;

  dealloc_temp(ctx, 4 + 256 + 1 + 1 + 1);
}

void emit_lget(Context &ctx, const Token &a, const Token &b, const Token &c) {
  std::string varname = std::get<std::string>(a.value);
  VarDetail a_var = get_var_detail(ctx, varname);
  if (!a_var.is_list)
    throw "not a list";
  size_t aid = a_var.id;

  varname = std::get<std::string>(c.value);
  VarDetail cvar = get_var_detail(ctx, varname);
  if (cvar.is_list)
    throw "c is not a var";
  size_t cid = cvar.id;

  size_t tb = alloc_temp(ctx, 3);
  size_t tfence1 = tb + 1;
  size_t tfence0 = tb + 2;

  // tb|tf| 0|ti|..|..|..|**| 0|tf|tc

  // tb = b;
  emit_internal_set(ctx, b, tb);

  // c = 0
  emit_internal_clear(ctx, cid);

  // set tfence = 1
  emit_internal_clear(ctx, tfence0);
  emit_internal_clear(ctx, tfence1);
  go_to(ctx, tfence1);
  add_value(ctx, 1);

  size_t ti = alloc_temp(ctx, 256 + 1 + 1 + 1 + 1);

  go_to(ctx, ti);
  ctx.prog += ">";
  for (int i = 0; i < 256 + 1 + 1 + 1; i++)
    ctx.prog += "[-]>";
  for (int i = 0; i < 256 + 1 + 1 + 1 + 1; i++)
    ctx.prog += "<";

  size_t offset = ti - aid;
  emit_internal_copy(ctx, tb, ti);
  go_to(ctx, ti);
  ctx.prog += "[[->+<]>-]"; // go right tb times
  ctx.prog += ">>+<<";      // add fencing after the index

  // tb| 1| 0| 0|..|..|..|**| 0| 1| x
  //           ^ ti        ^ pos    ^ a[b] copy

  for (size_t i = 0; i < offset; i++)
    ctx.prog += '<';
  // now the position = a[b]

  { // while a[b]
    ctx.prog += "[";

    ctx.prog += "-";
    for (size_t i = 0; i < offset; i++)
      ctx.prog += '>';
    // now the pos is ti

    ctx.prog += ">>>+<<<"; // incr x
    // now the pos is ti
    for (size_t i = 0; i < offset; i++)
      ctx.prog += '<';
    // now the position = a[b]

    ctx.prog += "]";
  }

  for (size_t i = 0; i < offset; i++)
    ctx.prog += '>';
  // now the pos is ti
  ctx.prog += ">>>"; // now pos = x
  {
    ctx.prog += "[";
    ctx.prog += "-";
    ctx.prog += "<<<"; // now pos = ti

    // go to a[b], +, then go back to ti
    for (size_t i = 0; i < offset; i++)
      ctx.prog += '<';
    ctx.prog += "+";
    for (size_t i = 0; i < offset; i++)
      ctx.prog += '>';

    ctx.prog += left_until_one; // go left until found 1 (the left fence)
    ctx.last_pos = tfence1;
    go_to(ctx, cid);
    ctx.prog += "+";
    go_to(ctx, tfence1);
    ctx.prog += ">>";
    ctx.prog += right_until_one; // go right until found 1 (the right fence)
    ctx.prog += ">";
    ctx.prog += "]";
  }

  ctx.prog += "<<<";
  ctx.prog += left_until_one; // go left until found 1 (the left fence)
  ctx.last_pos = tfence1;

  dealloc_temp(ctx, 3 + 256 + 1 + 1 + 1 + 1);
}

void emit_ifeq(Context &ctx, const Token &a, const Token &b) {
  size_t ta = alloc_temp(ctx, 3);
  size_t tb = ta + 1;
  size_t tcond = ta + 2;

  emit_internal_set(ctx, a, ta);
  emit_internal_set(ctx, b, tb);
  emit_internal_a_eq_b(ctx, ta, tb, tcond);

  go_to(ctx, tcond);
  ctx.prog += "[-";
  ctx.ends.push(BlockEndInstr{
      .initial_pos = ctx.last_pos,
      .final_pos = ctx.last_pos,
      .variables = 3,
      .cleanup = "]",
  });
}

void emit_ifneq(Context &ctx, const Token &a, const Token &b) {
  size_t ta = alloc_temp(ctx, 3);
  size_t tb = ta + 1;
  size_t tcond = ta + 2;

  emit_internal_set(ctx, a, ta);
  emit_internal_set(ctx, b, tb);
  emit_internal_a_neq_b(ctx, ta, tb, tcond);

  go_to(ctx, tcond);
  ctx.prog += "[-";
  ctx.ends.push(BlockEndInstr{
      .initial_pos = ctx.last_pos,
      .final_pos = ctx.last_pos,
      .variables = 3,
      .cleanup = "]",
  });
}

void emit_wneq(Context &ctx, const Token &a, const Token &b) {
  size_t ta = alloc_temp(ctx, 3);
  size_t tb = ta + 1;
  size_t tcond = ta + 2;

  size_t prog_size = ctx.prog.length();
  size_t initial_pos = ctx.last_pos;

  emit_internal_set(ctx, a, ta);
  emit_internal_set(ctx, b, tb);
  emit_internal_a_neq_b(ctx, ta, tb, tcond);
  go_to(ctx, tcond);
  std::string cond = ctx.prog.substr(prog_size);

  ctx.prog += "[";
  ctx.ends.push(BlockEndInstr{
      .initial_pos = initial_pos,
      .final_pos = ctx.last_pos,
      .variables = 3,
      .cleanup = cond + "]",
  });
}

std::string kcuf(const std::string &code) {
  try {
    std::vector<Token> tokens = tokenize(code);

    size_t last_used_var_id = 0;
    std::unordered_map<std::string, std::stack<VarDetail>>
        variables; // var name -> var index
    std::unordered_map<std::string, ProcDetail>
        proc_maps; // proc name -> detail

    for (size_t i = 0; i < tokens.size(); i++)
      if (tokens[i].kind == Var)
        for (i = i + 1; i < tokens.size() && tokens[i].kind != EOL; i++) {
          if (!variables[std::get<std::string>(tokens[i].value)].empty())
            throw "variable redefined";

          bool is_list = tokens[i + 1].kind == OpenSquare;

          variables[std::get<std::string>(tokens[i].value)].push(
              VarDetail{.id = last_used_var_id++, .is_list = is_list});
          if (tokens[i + 1].kind == OpenSquare) {
            int size = std::get<int>(tokens[i + 2].value);
            if (i + 3 >= tokens.size() || tokens[i + 3].kind != CloseSquare)
              throw "missing close square";
            i += 3;
            last_used_var_id += size - 1;
          }
        }

    for (size_t i = 0; i < tokens.size(); i++)
      if (tokens[i].kind == Proc) {
        size_t start = i;

        i++;
        std::string name = std::get<std::string>(tokens[i].value);

        std::vector<std::string> params;
        for (i++; i < tokens.size() && tokens[i].kind != EOL; i++) {
          std::string name = std::get<std::string>(tokens[i].value);
          for (auto x : params)
            if (x == name)
              throw "duplicate proc param";
          params.push_back(name);
        }

        size_t level = 1;
        for (i++; i < tokens.size() && level > 0; i++) {
          if (tokens[i].kind == IfEq || tokens[i].kind == IfNeq ||
              tokens[i].kind == WNeq)
            level++;
          else if (tokens[i].kind == End)
            level--;
          else if (tokens[i].kind == Proc)
            throw "nested proc";
          else if (tokens[i].kind == Var)
            throw "var inside proc";
        }

        if (level != 0)
          throw "unmatch block";

        i--;
        if (proc_maps.find(name) != proc_maps.end())
          throw "duplicate proc";
        proc_maps[name] = ProcDetail{
            .token_idx = start, .end_idx = i, .params = std::move(params)};
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
        emit_a2b(context, tokens[i + 1], tokens[i + 2], tokens[i + 3],
                 tokens[i + 4]);
        i += 5;
        break;
      case B2A:
        emit_b2a(context, tokens[i + 1], tokens[i + 2], tokens[i + 3],
                 tokens[i + 4]);
        i += 5;
        break;

      case LSet:
        emit_lset(context, tokens[i + 1], tokens[i + 2], tokens[i + 3]);
        i += 4;
        break;
      case LGet:
        emit_lget(context, tokens[i + 1], tokens[i + 2], tokens[i + 3]);
        i += 4;
        break;

      case IfEq:
        emit_ifeq(context, tokens[i + 1], tokens[i + 2]);
        i += 3;
        break;

      case IfNeq:
        emit_ifneq(context, tokens[i + 1], tokens[i + 2]);
        i += 3;
        break;

      case WNeq:
        emit_wneq(context, tokens[i + 1], tokens[i + 2]);
        i += 3;
        break;

      case Proc: {
        std::string proc_name = std::get<std::string>(tokens[i + 1].value);
        i = context.proc_maps[proc_name].end_idx;
      } break;

      case Call: {
        i++;
        std::string proc_name = std::get<std::string>(tokens[i].value);

        std::vector<VarDetail> var_args;
        for (i++; i < tokens.size() && tokens[i].kind != EOL; i++) {
          std::string arg = std::get<std::string>(tokens[i].value);
          VarDetail vardetail = get_var_detail(context, arg);
          var_args.push_back(vardetail);
        }

        if (context.proc_maps.find(proc_name) == context.proc_maps.end())
          throw "missing procedure";

        ProcDetail proc_detail = context.proc_maps[proc_name];
        if (var_args.size() != proc_detail.params.size())
          throw "unmatch args";
        for (size_t j = 0; j < proc_detail.params.size(); j++)
          context.variables[proc_detail.params[j]].push(var_args[j]);

        context.ends.push(BlockEndInstr{
            .is_call = true, .function_name = proc_name, .next_pc = i});
        if (context.called_procs.find(proc_name) != context.called_procs.end())
          throw "recursive";
        context.called_procs.insert(proc_name);

        i = proc_detail.token_idx;
        while (i < tokens.size() && tokens[i].kind != EOL)
          i++;
      } break;
      case End: {
        if (context.ends.empty())
          throw "nothing to end";
        BlockEndInstr cleanup = context.ends.top();
        if (cleanup.is_call) {
          ProcDetail proc_detail = context.proc_maps[cleanup.function_name];
          context.called_procs.erase(cleanup.function_name);
          for (size_t j = 0; j < proc_detail.params.size(); j++)
            context.variables[proc_detail.params[j]].pop();
          i = cleanup.next_pc;
        } else {
          go_to(context, cleanup.initial_pos);
          context.prog += cleanup.cleanup;
          dealloc_temp(context, cleanup.variables);
          context.last_pos = cleanup.final_pos;
        }
        context.ends.pop();
      } break;

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
      case EOL:
        break;
      default:
        throw error_msg;
        break;
      }

      context.prog.push_back('\n');
    }

    if (!context.ends.empty())
      throw "unclosed block";

    return context.prog;
  } catch (...) {
    throw error_msg;
  }
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

  /*
  std::string result = kcuf("var X K\n\
read X\n\
cmp 80 X K\n\
msg X K\n\
cmp X 'z' K\n\
msg X K\n\
cmp X X K\n\
msg X K");
  */

  /*
  std::string result = kcuf("var A B C D\n\
set a 247\n\
b2a A B C D\n\
msg A B C D\n\
inc B 1\n\
dec C 2\n\
inc D 5\n\
a2b B C D A\n\
msg A B C D // A = (100 * (2 + 1) + 10 * (4 - 2) + (7 + 5)) % 256 = 76 =
0x4c)");
  */

  /*
    std::string result = kcuf("var L  [ 20 ]  I X\n\
lset L 10 80\n\
set X 20\n\
lset L 5 X\n\
set X 9\n\
lset L X X\n\
set I 4\n\
lget L I X\n\
msg X\n\
lget L 5 X\n\
msg X\n\
lget L 9 X\n\
msg X\n\
lget L 10 X\n\
msg X\n\
lget L 19 X\n\
msg X");
*/

  /*
  std::string result = kcuf("var A[5] B C\n\
set B 10\n\
set C 100\n\
lset A 3 C\n\
lset A 1 B\n\
lget A 1 C\n\
lget A 3 B\n\
msg B C");
  */

  /*
  std::string result = kcuf("var A[5] B C\n\
set B 10\n\
set C 100\n\
lset A 0 C\n\
lget A 0 B\n\
msg B C");
*/

  /*
  std::string result = kcuf("\n\
var F L[5] X\n\
set F 0\n\
add 10 10 X\n\
wneq F 5\n\
        lset L F X\n\
        inc F 1\n\
        dec X 1\n\
end\n\
//L == [20,19,18,17,16]\n\
\n\
wneq F 0\n\
        inc F -1\n\
        lget L F X\n\
        msg X\n\
end\n\
\n\
set F 10\n\
wneq F 0\n\
        ifeq F 10\n\
                set F 5\n\
        end\n\
        dec F 1\n\
        lget L F X\n\
        ifneq X 18\n\
                msg F X\n\
        end\n\
end\n\
ifeq F 0\n\
        ifneq X 50\n\
                msg \";-)\"\n\
        end\n\
end\n\
");
  */

  /*
  std::string result = kcuf("\n\
var F L[5] X\n\
set F 0\n\
add 10 10 X\n\
wneq F 5\n\
        lset L F X\n\
        inc F 1\n\
        dec X 1\n\
end\n\
//L == [20,19,18,17,16]\n\
\n\
wneq F 0\n\
        inc F -1\n\
        lget L F X\n\
        msg X\n\
end\n\
\n\
set F 10\n\
wneq F 0\n\
        ifeq F 10\n\
                set F 5\n\
        end\n\
        dec F 1\n\
        lget L F X\n\
        ifneq X 18\n\
                msg F X\n\
        end\n\
end\n\
ifeq F 0\n\
        ifneq X 50\n\
                msg \";-)\"\n\
        end\n\
end\n\
");
  */

  std::string result = kcuf("var A B T\n\
set A 'U'\n\
set B 'V'\n\
\n\
msg\"Outer Before : \"A B\"\\n\"\n\
call swap B A\n\
msg\"Outer After : \"A B\"\\n\"\n\
\n\
proc swap x y\n\
	msg \"Inner Before : \"x y\"\\n\"\n\
	set T x\n\
	call say T\n\
	set x y\n\
	set y T\n\
	msg \"Inner After : \"x y\"\\n\"\n\
end\n\
proc say x\n\
	msg \"It is \" x \" now\\n\"\n\
end");

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
    case ';':
      std::cerr << "Pos=" << pos << " Memory:" << std::endl;
      for (int i = 0; i < 100; i++)
        std::cerr << (int)memory[i] << " ";
      std::cerr << std::endl;
      break;
    default:
      break;
    }
  }
  std::cerr << std::endl;
  std::cerr << "Memory:" << std::endl;
  for (int i = 0; i < 100; i++)
    std::cerr << (int)memory[i] << " ";
  std::cerr << std::endl;
}
