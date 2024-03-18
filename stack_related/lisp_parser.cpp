//
// Created by luoxiYun on 2024/3/15.
//
#include <string>
#include <deque>
#include <list>
#include <unordered_map>

//leetcode 736 Lisp语法解析
class LispParser {

    enum class TokenType {
        LEFT_PARENTHESIS,
        RIGHT_PARENTHESIS,
        VAR,
        NUMBER,
        LET,
        ADD,
        MULT
    };

    struct Token {
        TokenType type;
        std::string value;
    };

    //declare a TokenStream class that have peek() and get() method
    class TokenStream {
        friend class LispParser;
        std::deque<Token> token_stream;

        Token peek() {
            return token_stream.front();
        }
        Token get() {
            Token t = token_stream.front();
            token_stream.pop_front();
            return t;
        }
        explicit TokenStream(std::list<Token> &tokens) : token_stream(tokens.begin(), tokens.end()){}
    };

    //call stack context
    class ExpressionContext{
        friend class LispParser;
        std::deque<std::unordered_map<std::string, int>> context;

        void addFrame(){
            context.emplace_front();
        }

        void popFrame(){
            context.pop_front();
        }

        void addVariable(const std::string &var, int value){
            context.front()[var] = value;
        }

        auto getVariable(const std::string &var){
            return context.front()[var];
        }

    };

    //given an expression like (let x 2 (mult x (let x 3 y 4 (add x y)))), please parse this expression into token list
    std::list<Token> &tokenizer(std::string &expression) {
        std::list<Token> tokens;
        for (int i = 0; i < expression.size(); i++) {
            if (expression[i] == '(') {
                tokens.push_back({TokenType::LEFT_PARENTHESIS, "("});
            } else if (expression[i] == ')') {
                tokens.push_back({TokenType::RIGHT_PARENTHESIS, ")"});
            } else if (expression[i] >= 'a' && expression[i] <= 'z'){
                int j = i + 1;
                while (expression[j] != ' ' && expression[j] != ')') {
                    j++;
                }
                auto var = expression.substr(i, j-i);
                if (var == "let"){
                    tokens.push_back({TokenType::LET, "let"});
                } else if (var == "add"){
                    tokens.push_back({TokenType::ADD, "add"});
                } else if (var == "mult"){
                    tokens.push_back({TokenType::MULT, "mult"});
                } else {
                    tokens.push_back({TokenType::VAR, var});
                }
            } else if(isdigit(expression[i])){
                int j = i + 1;
                while (isdigit(expression[j])){
                    j++;
                }
                tokens.push_back({TokenType::NUMBER, expression.substr(i, j-i)});
            } else {
                i++;
            }
        }
        return tokens;
    }

    auto eval_let(TokenStream &ts, ExpressionContext &context){
        ts.get();
        ts.get();
        int res = -1;
        context.addFrame();
        while (true){
            auto t1 = ts.peek();
            auto t2 = ts.peek();
            if (t1.type == TokenType::VAR &&t2.type != TokenType::RIGHT_PARENTHESIS){
                auto var = ts.get();
                auto value = evaluate_expr(ts, context);
                context.addVariable(var.value, value);
            } else {
                res = evaluate_expr(ts, context);
                break;
            }
        }
        context.popFrame();
        ts.get(); //parse ')'
        return res;
    }

    int evaluate_expr(TokenStream &ts, ExpressionContext &context){
        auto t1 = ts.peek();
        if (t1.type == TokenType::LEFT_PARENTHESIS){
            auto t2 = ts.peek();
            if (t2.type == TokenType::LET){
                return eval_let(ts, context);
            } else if (t2.type == TokenType::ADD){
                return eval_add(ts, context);
            } else if (t2.type == TokenType::MULT){
                return eval_mult(ts, context);
            }
        } else if (t1.type == TokenType::VAR){
            return eval_var(ts, context);
        } else if (t1.type == TokenType::NUMBER){
            return eval_number(ts);
        }
    }

    int eval_mult(TokenStream &ts, ExpressionContext &context){
        ts.get(); //parse 'mult'
        auto t1 = evaluate_expr(ts, context);
        auto t2 = evaluate_expr(ts, context);
        ts.get(); //parse ')'
        return t1 * t2;
    }

    int eval_add(TokenStream &ts, ExpressionContext &context){
        ts.get(); //parse 'add'
        auto t1 = evaluate_expr(ts, context);
        auto t2 = evaluate_expr(ts, context);
        ts.get(); //parse ')'
        return t1 + t2;
    }
    int eval_var(TokenStream &ts, ExpressionContext &context){
        auto t = ts.get();
        //字符串转成int32_t
        return context.getVariable(t.value);
    }
    int eval_number(TokenStream &ts){
        auto t = ts.get();
        return std::stoi(t.value);
    }

    //调用入口
    auto evaluate(std::string &expression){
        auto tokens = tokenizer(expression);
        TokenStream ts(tokens);
        ExpressionContext context;
        context.addFrame();
        return evaluate_expr(ts, context);
    }

};