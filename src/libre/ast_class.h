/*
 * Copyright 2018 Scott Vokes
 *
 * See LICENCE for the full copyright terms.
 */

#ifndef RE_AST_CLASS_H
#define RE_AST_CLASS_H

struct fsm;
struct fsm_state;
struct fsm_options;

enum re_char_class_flags {
	RE_CHAR_CLASS_FLAG_NONE = 0x00,
	/* the class should be negated, e.g. [^aeiou] */
	RE_CHAR_CLASS_FLAG_INVERTED = 0x01,
	/* includes the `-` character, which isn't part of a range */
	RE_CHAR_CLASS_FLAG_MINUS = 0x02
};

enum re_char_class_ast_type {
	RE_CHAR_CLASS_AST_CONCAT,
	RE_CHAR_CLASS_AST_LITERAL,
	RE_CHAR_CLASS_AST_RANGE,
	RE_CHAR_CLASS_AST_NAMED,
	RE_CHAR_CLASS_AST_CHAR_TYPE,
	RE_CHAR_CLASS_AST_FLAGS,
	RE_CHAR_CLASS_AST_SUBTRACT
};

enum ast_range_endpoint_type {
	AST_RANGE_ENDPOINT_LITERAL,
	AST_RANGE_ENDPOINT_CHAR_TYPE,
	AST_RANGE_ENDPOINT_CHAR_CLASS
};
struct ast_range_endpoint {
	enum ast_range_endpoint_type t;
	union {
		struct {
			unsigned char c;
		} literal;
		struct {
			char_class_constructor *ctor;
		} char_class;
	} u;
};

struct re_char_class_ast {
	enum re_char_class_ast_type t;
	union {
		struct {
			struct re_char_class_ast *l;
			struct re_char_class_ast *r;
		} concat;
		struct {
			unsigned char c;
		} literal;
		struct {
			struct ast_range_endpoint from;
			struct ast_pos start;
			struct ast_range_endpoint to;
			struct ast_pos end;
		} range;
		struct {
			char_class_constructor *ctor;
		} named;
		struct {
			enum re_char_class_flags f;
		} flags;
		struct {
			struct re_char_class_ast *ast;
			struct re_char_class_ast *mask;
		} subtract;
	} u;
};

struct re_char_class_ast *
re_char_class_ast_concat(struct re_char_class_ast *l,
    struct re_char_class_ast *r);

struct re_char_class_ast *
re_char_class_ast_literal(unsigned char c);

struct re_char_class_ast *
re_char_class_ast_range(const struct ast_range_endpoint *from, struct ast_pos start,
    const struct ast_range_endpoint *to, struct ast_pos end);

void
re_char_class_endpoint_span(const struct ast_range_endpoint *r,
    unsigned char *from, unsigned char *to);

struct re_char_class_ast *
re_char_class_ast_flags(enum re_char_class_flags flags);

struct re_char_class_ast *
re_char_class_ast_named_class(char_class_constructor *ctor);

struct re_char_class_ast *
re_char_class_ast_subtract(struct re_char_class_ast *ast,
    struct re_char_class_ast *mask);

void
re_char_class_ast_free(struct re_char_class_ast *ast);

int
re_char_class_ast_compile(struct re_char_class_ast *cca,
    struct fsm *fsm, enum re_flags flags,
    struct re_err *err, const struct fsm_options *opt,
    struct fsm_state *x, struct fsm_state *y);

#endif
