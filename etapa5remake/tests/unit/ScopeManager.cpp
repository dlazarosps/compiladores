#include "../../include/ScopeManager.h"
#include "../../include/SymbolTable.h"
#include "../../include/SymbolTableEntry.h"
#include <gtest/gtest.h>
#include <string>

// TODO: develop fixtures for the data

TEST(ScopeManager, AddAndLookupCorrect) {
    SymbolTableEntry* entry1 = new SymbolTableEntry("1",0,0,0,0);
    SymbolTableEntry* entry2 = new SymbolTableEntry("2",0,0,0,0);
    SymbolTableEntry* entry3 = new SymbolTableEntry("3",0,0,0,0);
    SymbolTableEntry* entry4 = new SymbolTableEntry("1",0,0,0,0);
    SymbolTableEntry* entry5 = new SymbolTableEntry("2",0,0,0,0);
    SymbolTableEntry* entry6 = new SymbolTableEntry("3",0,0,0,0);

    // Creates the scope manager, which starts in the global scope
    ScopeManager *scopeManager = new ScopeManager();
    // Add entries to the global scope
    scopeManager->InsertEntry(entry1);
    scopeManager->InsertEntry(entry2);
    scopeManager->InsertEntry(entry3);

    // Creates a symbol table, populate it and then attaches it to the scope manager
    SymbolTable* tableFoo = new SymbolTable("foo");
    tableFoo->Insert(entry4);
    tableFoo->Insert(entry5);
    scopeManager->AddFunctionScope(tableFoo);

    // Attaches a new symbol table and then populate it
    SymbolTable* tableBar = new SymbolTable("bar");
    scopeManager->AddFunctionScope(tableBar);
    scopeManager->SetCurrentScope("bar");
    scopeManager->InsertEntry(entry6);

    // Go back to the global scope
    scopeManager->SetCurrentScopeToGlobal();

    ASSERT_EQ(0,scopeManager->HasScope("_GLOBAL_"));
    ASSERT_EQ(0,scopeManager->HasScope("foo"));
    ASSERT_EQ(0,scopeManager->HasScope("bar"));
    ASSERT_EQ(-1,scopeManager->HasScope("UNDEFINED"));

    ASSERT_EQ(0,scopeManager->GetCurrentScope().compare("_GLOBAL_"));
    ASSERT_EQ(entry1,scopeManager->LookUp("1"));
    ASSERT_EQ(entry2,scopeManager->LookUp("2"));
    ASSERT_EQ(entry3,scopeManager->LookUp("3"));
    ASSERT_EQ(NULL,scopeManager->LookUp("4"));

    // Go to the scope of the function "foo"
    scopeManager->SetCurrentScope("foo");

    ASSERT_EQ(0,scopeManager->GetCurrentScope().compare("foo"));
    ASSERT_EQ(entry4,scopeManager->LookUp("1"));
    ASSERT_EQ(entry5,scopeManager->LookUp("2"));
    ASSERT_EQ(entry3,scopeManager->LookUp("3"));
    ASSERT_EQ(NULL,scopeManager->LookUp("4"));

    // Go to the scope of the function "bar"
    scopeManager->SetCurrentScope("bar");

    ASSERT_EQ(0,scopeManager->GetCurrentScope().compare("bar"));
    ASSERT_EQ(entry1,scopeManager->LookUp("1"));
    ASSERT_EQ(entry2,scopeManager->LookUp("2"));
    ASSERT_EQ(entry6,scopeManager->LookUp("3"));
    ASSERT_EQ(NULL,scopeManager->LookUp("4"));
}
