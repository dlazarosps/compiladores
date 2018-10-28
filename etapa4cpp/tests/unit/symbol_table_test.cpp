// tests.cpp
#include "../../include/symbol_table.h"
#include <gtest/gtest.h>
#include <string>

// TODO: develop fixtures for the data

TEST(SymbolTableTest, AddAndLookupCorrect) {
    SymbolTableEntry* entry1 = new SymbolTableEntry("foo");
    SymbolTableEntry* entry2 = new SymbolTableEntry("bar");
    SymbolTableEntry* entry3 = new SymbolTableEntry("var");
    SymbolTable* table = new SymbolTable();
    table->Insert(entry1);
    table->Insert(entry2);
    table->Insert(entry3);

    ASSERT_EQ(entry2,table->LookUp("bar"));
}

TEST(SymbolTableTest, AddAndLookupFalse) {
    SymbolTableEntry* entry1 = new SymbolTableEntry("foo");
    SymbolTableEntry* entry2 = new SymbolTableEntry("bar");
    SymbolTableEntry* entry3 = new SymbolTableEntry("var");
    SymbolTable* table = new SymbolTable();
    table->Insert(entry1);
    table->Insert(entry2);
    table->Insert(entry3);

    ASSERT_EQ(NULL,table->LookUp("does not exist"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
