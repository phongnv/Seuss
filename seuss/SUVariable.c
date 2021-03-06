//
//  SUVariable.c
//  seuss
//
//  Created by Cory Kilger on 7/20/12.
//  Copyright (c) 2012 Cory Kilger. All rights reserved.
//

#include "SUVariable.h"
#include "SUTypeInternal.h"
#include "SUTokenizer.h"
#include "SUString.h"
#include "SUList.h"

struct seuss_variable {
    SUType __base;
    SUList * name;
    SUTypeRef value;
};

void seuss_variable_free(SUTypeRef type) {
    SUVariable * variable = type;
    if (variable->name)
        SURelease(variable->name);
    if (variable->value)
        SURelease(variable->value);
    seuss_free(variable);
}

SUVariable * SUVariableCreate(struct seuss_list * name) {
    SUVariable * variable = malloc(sizeof(SUVariable));
    SUInitialize(variable, NULL, NULL, seuss_variable_free);
    variable->name = SURetain(name);
    variable->value = NULL;
    return variable;
}

struct seuss_list * SUVariableGetName(SUVariable * variable) {
    return variable->name;
}

SUTypeRef SUVariableGetValue(SUVariable * variable) {
    return variable->value;
}

void SUVariableSetValue(SUVariable * variable, void * value) {
    if (value != variable->value) {
        if (variable->value)
            SURelease(variable->value);
        if (value)
            SURetain(value);
        variable->value = value;
    }
}

int SUTypeIsVariable(SUType * type) {
    return (type->free == seuss_variable_free);
}

struct seuss_list * SUVariableCreateBuiltins() {
    SUList * variables = SUListCreate();
    
    SUList * tokens = SUListCreate();
    
    SUString * value = SUStringCreate("\n");
    SUString * builtinFile = SUStringCreate("** built-in **");
    SUToken * newToken = SUTokenCreate(SUTokenTypeWord, "new", builtinFile, 0);
    SUToken * lineToken = SUTokenCreate(SUTokenTypeWord, "line", builtinFile, 0);
    SUListAddValue(tokens, newToken);
    SUListAddValue(tokens, lineToken);
    SUVariable * newLine = SUVariableCreate(tokens);
    SUVariableSetValue(newLine, value);
    SUListAddValue(variables, newLine);
    SURelease(newLine);
    SURelease(tokens);
    SURelease(newToken);
    SURelease(lineToken);
    SURelease(builtinFile);
    SURelease(value);
    
    return variables;
}