#include "../../include/lexical_value.h"
#include <gtest/gtest.h>
#include <string>
#include <string.h>

TEST(LexicalValue, TestValueSetting1) {
    char lexWord[] = {'w','o','r','d','\0'};
    char lexWord2[] = {'2','\0'};
    string wordToCompare = "word";
    string wordToCompare2 = "2";

    LexicalValue *lex1 = new LexicalValue(10, TIPO_PALAVRA_RESERVADA, VALOR_STRING, lexWord);
    LexicalValue *lex2 = new LexicalValue(-99, TIPO_LITERAL, VALOR_INT, lexWord2);

    ASSERT_EQ(10, lex1->GetLine());
    ASSERT_EQ(TIPO_PALAVRA_RESERVADA, lex1->GetType());
    ASSERT_EQ(VALOR_STRING, lex1->GetValueType());
    ASSERT_EQ(0,wordToCompare.compare(*(lex1->GetValue().stringValue)));
    ASSERT_EQ(0,wordToCompare.compare(lex1->ValueToString()));

    ASSERT_EQ(-99, lex2->GetLine());
    ASSERT_EQ(TIPO_LITERAL, lex2->GetType());
    ASSERT_EQ(VALOR_INT, lex2->GetValueType());
    ASSERT_EQ(2,lex2->GetValue().intValue);
    ASSERT_EQ(0,wordToCompare2.compare(lex2->ValueToString()));

    ASSERT_NE(0,(lex1->ValueToString()).compare(lex2->ValueToString()));
}
