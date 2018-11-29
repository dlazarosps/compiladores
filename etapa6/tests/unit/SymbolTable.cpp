#include "../../include/SymbolTable.h"
#include "../../include/SymbolTableEntry.h"
#include <gtest/gtest.h>
#include <string>

// TODO: develop fixtures for the data

TEST(SymbolTable, AddAndLookupCorrect) {
    SymbolTableEntry* entry1 = new SymbolTableEntry("foo",0,0,0);
    SymbolTableEntry* entry2 = new SymbolTableEntry("bar",0,0,0);
    SymbolTableEntry* entry3 = new SymbolTableEntry("var",0,0,0);
    SymbolTable* table = new SymbolTable("a");
    table->Insert(entry1);
    table->Insert(entry2);
    table->Insert(entry3);

    ASSERT_EQ(entry2,table->LookUp("bar"));
}

TEST(SymbolTable, AddAndLookupFalse) {
    SymbolTableEntry* entry1 = new SymbolTableEntry("foo",0,0,0);
    SymbolTableEntry* entry2 = new SymbolTableEntry("bar",0,0,0);
    SymbolTableEntry* entry3 = new SymbolTableEntry("var",0,0,0);
    SymbolTable* table = new SymbolTable("b");
    table->Insert(entry1);
    table->Insert(entry2);
    table->Insert(entry3);

    ASSERT_EQ(NULL,table->LookUp("does not exist"));
}
