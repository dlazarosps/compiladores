#include "../../include/lexical_value.h"
#include "../../include/ast.h"
#include <gtest/gtest.h>
#include <string>

// TODO: develop fixtures

TEST(AbstractSyntaxTree, TestValueSetting1) {
    char lexWord[] = {'w','o','r','d','\0'};
    char lexWord2[] = {'2','\0'};
    char lexWord3[] = {'t','r','u','e','\0'};

    LexicalValue *lex1 = new LexicalValue(10, TIPO_PALAVRA_RESERVADA, VALOR_STRING, lexWord);
    LexicalValue *lex2 = new LexicalValue(11, TIPO_LITERAL, VALOR_INT, lexWord2);
    LexicalValue *lex3 = new LexicalValue(12, TIPO_LITERAL, VALOR_BOOL, lexWord3);

    AbstractSyntaxTree *node1 = new AbstractSyntaxTree(AST_PROGRAMA, lex1);
    AbstractSyntaxTree *node2 = new AbstractSyntaxTree(AST_PROGRAMA, lex2);
    AbstractSyntaxTree *node3 = new AbstractSyntaxTree(AST_PROGRAMA, lex3);
    AbstractSyntaxTree *node4 = new AbstractSyntaxTree(AST_PROGRAMA, lex1);

    node1->AddLeaf(node2);
    node2->AddLeaf(node3);
    node2->AddLeaf(node4);

    ASSERT_EQ(1, node1->GetLeafsSize());
    ASSERT_EQ(2, node2->GetLeafsSize());
    ASSERT_EQ(0, node3->GetLeafsSize());
    ASSERT_EQ(0, node4->GetLeafsSize());

    string word = "word";

    ASSERT_EQ(0, word.compare(node1->GetNodeLeaf(0)->GetNodeLeaf(1)->GetLexicalValue()->ValueToString()));
}
