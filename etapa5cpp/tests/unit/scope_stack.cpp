#include "../../include/scope_stack.h"
#include "../../include/symbol_table.h"
#include <gtest/gtest.h>
#include <string>

// TODO: develop fixtures for the data

TEST(ScopeStack, AddAndLookupCorrect) {
    SymbolTableEntry* entry1 = new SymbolTableEntry("1",0,0,0);
    SymbolTableEntry* entry2 = new SymbolTableEntry("2",0,0,0);
    SymbolTableEntry* entry3 = new SymbolTableEntry("3",0,0,0);
    SymbolTableEntry* entry4 = new SymbolTableEntry("1",0,0,0);
    SymbolTableEntry* entry5 = new SymbolTableEntry("2",0,0,0);
    SymbolTableEntry* entry6 = new SymbolTableEntry("1",0,0,0);

    SymbolTable* table1 = new SymbolTable();
    table1->Insert(entry1);
    table1->Insert(entry2);
    table1->Insert(entry3);

    SymbolTable* table2 = new SymbolTable();
    table2->Insert(entry4);
    table2->Insert(entry5);

    SymbolTable* table3 = new SymbolTable();
    table3->Insert(entry6);

    ScopeStack *scope = new ScopeStack();

    scope->push(table1);
    scope->push(table2);
    scope->push(table3);

    ASSERT_EQ(entry6,scope->LookUp("1"));
    ASSERT_EQ(entry5,scope->LookUp("2"));
    ASSERT_EQ(entry3,scope->LookUp("3"));

    scope->pop();

    ASSERT_EQ(entry4,scope->LookUp("1"));
    ASSERT_EQ(entry5,scope->LookUp("2"));
    ASSERT_EQ(entry3,scope->LookUp("3"));

    scope->pop();

    ASSERT_EQ(entry1,scope->LookUp("1"));
    ASSERT_EQ(entry2,scope->LookUp("2"));
    ASSERT_EQ(entry3,scope->LookUp("3"));

    scope->pop();

    ASSERT_EQ(NULL,scope->LookUp("1"));
    ASSERT_EQ(NULL,scope->LookUp("2"));
    ASSERT_EQ(NULL,scope->LookUp("3"));
}
