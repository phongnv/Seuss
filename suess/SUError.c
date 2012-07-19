//
//  SUError.c
//  suess
//
//  Created by Cory Kilger on 7/18/12.
//  Copyright (c) 2012 Cory Kilger. All rights reserved.
//

#include "SUError.h"
#include "SUTypeInternal.h"
#include "SUString.h"

struct suess_error {
    SUType __base;
    SUErrorType type;
    SUString * file;
    unsigned int line;
    SUString * message;
};

void suess_error_free(SUTypeRef type) {
    SUError * error = type;
    if (error->file)
        SURelease(error->file);
    if (error->message)
        SURelease(error->message);
    suess_free(error);
}

SUError * SUErrorCreate(SUErrorType type, struct suess_string * file, unsigned int line, struct suess_string * message) {
    SUError * error = malloc(sizeof(SUError));
    SUInitialize(error, NULL, NULL, suess_error_free);
    error->type = type;
    error->file = SURetain(file);
    error->line = line;
    error->message = SURetain(message);
    return error;
}

SUErrorType SUErrorGetType(SUError * error) {
    return error->type;
}

struct suess_string * SUErrorGetFile(SUError * error) {
    return error->file;
}

unsigned int SUErrorGetLine(SUError * error) {
    return error->line;
}

struct suess_string * SUErrorGetMessage(SUError * error) {
    return error->message;
}