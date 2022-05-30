#include <stdio.h>

#define STACK_SIZE 256

/* The column and line are used to indicate where an error has occurred in the
   source text. */
int col  = 1; /*!< Cursor column number. */
int line = 1; /*!< Cursor line number. */

/* We save the line/col number of the last seen single/double quote. In this
   way, if a single/double quote is unmatched, we can report the location
   of the last seen single/double quote. The valid_*_quote boolean helps
   us check whether all quotes have been matched.*/
int valid_double_quotes    = 1;
int last_double_quote_line = 0;
int last_double_quote_col  = 0;
int valid_single_quotes    = 1;
int last_single_quote_line = 0;
int last_single_quote_col  = 0;

/* We use a stack to verify match opening and closing brackets. */
char bracket_stack[256] = {0}; /*!< Stack used to save 'open' brackets. */
int stack_top = 0; /*!< bracket_stack top: points at the next empty slot. */

/*!
 * \brief Print the line number and column number at which an error occurred.
 */
void report_error();

/*!
 * \brief Wrapper around getchar().
 *
 * getchar_knr() return the next character in the input stream. The added
 * twist here is that getchar_knr() will increment the global line and col
 * count after retrieving the next character as well as update the single/
 * double quote globals.
 *
 * \return The next character available in STDIN. EOF is returned if the
 *         end of file marker is reached.
 */
int getchar_knr();

/*!
 * \brief Return 1 if \a c is a bracket char.
 *
 * Bracket characters are any one of '(', '{', '[', ')', '}', or ']'.
 */
int is_bracket(char c);

/*!
 * \brief Return 1 if \a c is an opening bracket char (i.e., '(', '{', or '[').
 */
int is_opening_bracket(char c);

/*!
 * \brief Return 0 if \a c has a matching bracket at the top of bracket_stack.
 *
 * bracket_check() checks to see if \a c is the closing bracket to the opening
 * bracket at the top of bracket_stack.
 */
int bracket_check(char c);

/*!
 * \brief Return 0 if the next character is a valid esc sequence character.
 *
 * See https://en.wikipedia.org/wiki/Escape_sequences_in_C#Table_of_escape_sequences
 * for a list of valid esc sequence chars.
 *
 * \return 0 is returned if the next character read is a valid esc character.
 *         Otherwise, the next character that was read is returned.
 */
int escape_seq_check();

/*!
 * \brief Return 0 if a well-formed comment is processed.
 *
 * comment_check() scans the source code consuming an inline or block comment
 * in the source.
 */
int comment_check();

int main()
{
    int c = 0;
    while ((c = getchar_knr()) != EOF) {
        if (is_bracket(c)) {
            if (is_opening_bracket(c)) {
                /* Opening brackets just get pushed onto bracket_stack. */
                bracket_stack[stack_top++] = c;
            } else {
                /* A closing bracket's 'buddy' must be detected by
                   bracket_check() otherwise we have to report the error. */
                if (bracket_check(c)) {
                    report_error();
                    printf("mismatched bracket '%c'\n", c);

                    return 1;
                }
            }
        } else if ('\\' == c) {
            /* We have the start of an esc sequence. Check that the next char
               on the input stream is a valid esc char. */
            int is_valid_esc = 0;
            if ((is_valid_esc = escape_seq_check())) {
                report_error();
                printf("unknown escape character '%c'\n", is_valid_esc);

                return 1;
            }
        } else if ('/' == c) {
            /* We potentially have the start of a new inline or block comment.
               Call comment_check() to consume that comment or report an error
               if the comment is found to be malformed. */
            int start_line = line;
            int start_col  = col - 1;
            if (comment_check()) {
                line = start_line;
                col  = start_col;
                report_error();
                printf("malformed comment\n");

                return 1;
            }
        }
    }

    /* If we are done processing the source but there remains brackets on
       bracket_stack, the source contains one or more unclosed brackets
       that we must report. */
    if (stack_top) {
        report_error();
        printf("%c was not closed\n", bracket_stack[stack_top - 1]);

        return 1;
    }

    if (!valid_double_quotes) {
        line = last_double_quote_line;
        col  = last_double_quote_col;
        report_error();
        printf("mistmatched '\"'\n");

        return 1;
    }

    if (!valid_single_quotes) {
        line = last_single_quote_line;
        col  = last_single_quote_col;
        report_error();
        printf("mistmatched '\''\n");

        return 1;
    }

    return 0;
}

void report_error()
{
    printf("error on line %d column %d: ", line, col);
}

int getchar_knr()
{
    int c = getchar();
    if ('\n' == c) {
        line++;
        col = 0;
    } else if ('\'' == c) {
        last_single_quote_line = line;
        last_single_quote_col  = col;
        valid_single_quotes = !valid_single_quotes;
    } else if ('\"' == c) {
        last_double_quote_line = line;
        last_double_quote_col  = col;
        valid_double_quotes = !valid_double_quotes;
    };

    col++;

    return c;
}

int is_bracket(char c)
{
    return (('{'  == c) ||
            ('('  == c) ||
            ('['  == c) ||
            ('}'  == c) ||
            (')'  == c) ||
            (']'  == c));
}

int is_opening_bracket(char c)
{
    return (('{'  == c) ||
            ('('  == c) ||
            ('['  == c));
}

int bracket_check(char c)
{
    if (!stack_top)
        return 1;

    char bracket = bracket_stack[--stack_top];
    int is_valid_pair = 0;
    if ('}' == c)
        is_valid_pair = ('{' == bracket);
    else if (')' == c)
        is_valid_pair = ('(' == bracket);
    else if (']' == c)
        is_valid_pair = ('[' == c);
    else if ('\'' == c)
        is_valid_pair = ('\'' == c);
    else if ('\"' == c)
        is_valid_pair = ('\"' == c);

    return !is_valid_pair;
}

int escape_seq_check()
{
    int c = getchar_knr();
    if (EOF == c)
        return 1;

    int valid_esc_char =
            !(('b' == c)  || ('n' == c) || ('t' == c) || ('\\' == c) ||
              ('a' == c)  || ('f' == c) || ('r' == c) || ('\'' == c) ||
              ('\"' == c) || ('v' == c));

    return (valid_esc_char ? c : 0);
}

int comment_check()
{
    /* The code that follows implements a state machine for matching inline
       and block style C comments. It's more than a little gross given that
       we haven't introduced switches or enums just yet... */
    int start_state = 0;
    int end_state   = 5;
    int err_state   = 6;
    int c           = getchar_knr();
    int state       = start_state;
    while (1) {
        if (0 == state) {
            if ('/' == c)
                state = 1;
            else if ('*' == c)
                state = 2;
            else
                state = end_state;
        } else if (1 == state) {
            if ((EOF == c) || ('\n' == c))
                state = end_state;
        } else if (2 == state) {
            if ('*' == c)
                state = 4;
            else if (EOF == c)
                state = err_state;
            else
                state = 3;
        } else if (3 == state) {
            if ('*' == c)
                state = 4;
            else if (EOF == c)
                state = err_state;
        } else if (4 == state) {
            if ('/' == c)
                state = end_state;
            else if (EOF == c)
                state = err_state;
            else
                state = 3;
        } else if (err_state == state) {
            return 1;
        } else if (end_state == state) {
            return 0;
        }

        c = getchar_knr();
    }

    return 1; /* Unreachable */
}
