/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NATIVE_HANDLE_H_
#define NATIVE_HANDLE_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

typedef struct
{
    int version;        /* sizeof(native_handle) */
    int numFds;         /* number of file-descriptors at &data[0] */
    int numInts;        /* number of ints at &data[numFds] */
    int data[0];        /* numFds + numInts ints */
} native_handle;


/*
 * native_handle_dup
 * 
 * duplicates a native handle. All source file descriptors are dup()'ed.
 * 
 * lhs.numFds must be 0 or match rhs.numFds
 * lhs.numInts must be 0 or match rhs.numInts
 * 
 * if lhs.numFds and lhs.numInts are set to 0, they are the only fields
 * updated, this can be used to figure out the size needed for copying rhs.
 * 
 * return 0 on success, or a negative error code on failure
 * 
 */
int native_handle_dup(native_handle* lhs, native_handle const* rhs);


/*
 * native_handle_close
 * 
 * closes the file descriptors contained in this native_handle
 * 
 * return 0 on success, or a negative error code on failure
 * 
 */
int native_handle_close(const native_handle* h);


/*
 * native_handle_create
 * 
 * creates a native_handle and initializes it. must be destroyed with
 * native_handle_delete().
 * 
 */
native_handle* native_handle_create(int numFds, int numInts);

/*
 * native_handle_delete
 * 
 * frees a native_handle allocated with native_handle_create().
 * This ONLY frees the memory allocated for the native_handle, but doesn't
 * close the file descriptors; which can be achieved with native_handle_close().
 * 
 * return 0 on success, or a negative error code on failure
 * 
 */
int native_handle_delete(native_handle* h);


/*
 * native_handle_copy
 * 
 * makes a deep copy of rhs. If rhs is null, returns null.
 * 
 */
native_handle* native_handle_copy(const native_handle* rhs);


__END_DECLS

#endif /* NATIVE_HANDLE_H_ */
