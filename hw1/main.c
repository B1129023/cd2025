#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

// 手動定義判斷字元類型的函式
int is_alpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

int is_alnum(char ch) {
    return is_alpha(ch) || is_digit(ch);
}

int is_space(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}

// Token 類型定義
typedef enum {
    TYPE_TOKEN,
    MAIN_TOKEN,
    ID_TOKEN,
    LITERAL_TOKEN,
    ASSIGN_TOKEN,
    EQUAL_TOKEN,
    LEFTPAREN_TOKEN,
    REFTPAREN_TOKEN,
    LEFTBRACE_TOKEN,
    REFTBRACE_TOKEN,
    IF_TOKEN,
    ELSE_TOKEN,
    WHILE_TOKEN,
    PLUS_TOKEN,
    MINUS_TOKEN,
    SEMICOLON_TOKEN,
    UNKNOWN_TOKEN
} TokenType;

// Token 類型對應字串
const char* get_token_name(TokenType type) {
    switch (type) {
        case TYPE_TOKEN: return "TYPE_TOKEN";
        case MAIN_TOKEN: return "MAIN_TOKEN";
        case ID_TOKEN: return "ID_TOKEN";
        case LITERAL_TOKEN: return "LITERAL_TOKEN";
        case ASSIGN_TOKEN: return "ASSIGN_TOKEN";
        case EQUAL_TOKEN: return "EQUAL_TOKEN";
        case LEFTPAREN_TOKEN: return "LEFTPAREN_TOKEN";
        case REFTPAREN_TOKEN: return "REFTPAREN_TOKEN";
        case LEFTBRACE_TOKEN: return "LEFTBRACE_TOKEN";
        case REFTBRACE_TOKEN: return "REFTBRACE_TOKEN";
        case IF_TOKEN: return "IF_TOKEN";
        case ELSE_TOKEN: return "ELSE_TOKEN";
        case WHILE_TOKEN: return "WHILE_TOKEN";
        case PLUS_TOKEN: return "PLUS_TOKEN";
        case MINUS_TOKEN: return "MINUS_TOKEN";
        case SEMICOLON_TOKEN: return "SEMICOLON_TOKEN";
        default: return "UNKNOWN_TOKEN";
    }
}

// 判斷是否為關鍵字
TokenType check_keyword(const char* str) {
    if (strcmp(str, "int") == 0) return TYPE_TOKEN;
    if (strcmp(str, "main") == 0) return MAIN_TOKEN;
    if (strcmp(str, "if") == 0) return IF_TOKEN;
    if (strcmp(str, "else") == 0) return ELSE_TOKEN;
    if (strcmp(str, "while") == 0) return WHILE_TOKEN;
    return ID_TOKEN;
}

// Scanner 主體
void scan(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("無法開啟 main.c\n");
        return;
    }
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (is_space(ch)) continue;

        // 處理識別字或關鍵字
        if (is_alpha(ch) || ch == '_') {
            char buffer[MAX_TOKEN_LENGTH] = {0};
            int i = 0;
            buffer[i++] = ch;
            while ((ch = fgetc(fp)) != EOF && (is_alnum(ch) || ch == '_')) {
                if (i < MAX_TOKEN_LENGTH - 1)
                    buffer[i++] = ch;
            }
            buffer[i] = '\0';
            if (ch != EOF) ungetc(ch, fp);
            TokenType type = check_keyword(buffer);
            printf("%s: %s\n", buffer, get_token_name(type));
        }

        // 處理整數常數
        else if (is_digit(ch)) {
            char buffer[MAX_TOKEN_LENGTH] = {0};
            int i = 0;
            buffer[i++] = ch;
            while ((ch = fgetc(fp)) != EOF && is_digit(ch)) {
                if (i < MAX_TOKEN_LENGTH - 1)
                    buffer[i++] = ch;
            }
            buffer[i] = '\0';
            if (ch != EOF) ungetc(ch, fp);
            printf("%s: %s\n", buffer, get_token_name(LITERAL_TOKEN));
        }

        // 處理符號
        else {
            switch (ch) {
                case '=':
                    ch = fgetc(fp);
                    if (ch == '=') {
                        printf("==: %s\n", get_token_name(EQUAL_TOKEN));
                    } else {
                        if (ch != EOF) ungetc(ch, fp);
                        printf("=: %s\n", get_token_name(ASSIGN_TOKEN));
                    }
                    break;
                case '+':
                    printf("+: %s\n", get_token_name(PLUS_TOKEN)); break;
                case '-':
                    printf("-: %s\n", get_token_name(MINUS_TOKEN)); break;
                case '(':
                    printf("(: %s\n", get_token_name(LEFTPAREN_TOKEN)); break;
                case ')':
                    printf("): %s\n", get_token_name(REFTPAREN_TOKEN)); break;
                case '{':
                    printf("{: %s\n", get_token_name(LEFTBRACE_TOKEN)); break;
                case '}':
                    printf("}: %s\n", get_token_name(REFTBRACE_TOKEN)); break;
                case ';':
                    printf(";: %s\n", get_token_name(SEMICOLON_TOKEN)); break;
                default:
                    printf("%c: %s\n", ch, get_token_name(UNKNOWN_TOKEN));
            }
        }
    }
    fclose(fp);
}

int main() {
    char *filename = "hw1/main.c";

    scan(filename);
    return 0;
}
