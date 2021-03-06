/*
 * Copyright 1997-2006 Sun Microsystems, Inc.  All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 *  
 */
// This file is a derivative work resulting from (and including) modifications
// made by Azul Systems, Inc.  The date of such changes is 2010.
// Copyright 2010 Azul Systems, Inc.  All Rights Reserved.
//
// Please contact Azul Systems, Inc., 1600 Plymouth Street, Mountain View, 
// CA 94043 USA, or visit www.azulsystems.com if you need additional information 
// or have any questions.


#include "debug.hpp"
#include "globals.hpp"
#include "globalDefinitions.hpp"
#include "os.hpp"

// Basic error support

void basic_fatal(const char* msg) {
  fatal(msg);
}


// Something to help porters sleep at night

void check_basic_types() {
#ifdef ASSERT
  assert(min_intx ==  (intx)CONST64(0x8000000000000000), "correct constant");
  assert(max_intx ==  CONST64(0x7FFFFFFFFFFFFFFF), "correct constant");
  assert(max_uintx == CONST64(0xFFFFFFFFFFFFFFFF), "correct constant");
  assert( 8 == sizeof( intx),      "wrong size for basic type");
  assert( 8 == sizeof( jobject),   "wrong size for basic type");
  assert( (~max_juint) == 0,  "max_juint has all its bits");
  assert( (~max_uintx) == 0,  "max_uintx has all its bits");
  assert( (~max_julong) == 0, "max_julong has all its bits");
  assert( 1 == sizeof( jbyte),     "wrong size for basic type");
  assert( 2 == sizeof( jchar),     "wrong size for basic type");
  assert( 2 == sizeof( jshort),    "wrong size for basic type");
  assert( 4 == sizeof( juint),     "wrong size for basic type");
  assert( 4 == sizeof( jint),      "wrong size for basic type");
  assert( 1 == sizeof( jboolean),  "wrong size for basic type");
  assert( 8 == sizeof( jlong),     "wrong size for basic type");
  assert( 4 == sizeof( jfloat),    "wrong size for basic type");
  assert( 8 == sizeof( jdouble),   "wrong size for basic type");
  assert( 1 == sizeof( u1),        "wrong size for basic type");
  assert( 2 == sizeof( u2),        "wrong size for basic type");
  assert( 4 == sizeof( u4),        "wrong size for basic type");

  int num_type_chars = 0;
  for (int i = 0; i < 99; i++) {
    if (type2char((BasicType)i) != 0) {
      assert(char2type(type2char((BasicType)i)) == i, "proper inverses");
      num_type_chars++;
    }
  }
  assert(num_type_chars == 11, "must have tested the right number of mappings");
  assert(char2type(0) == T_ILLEGAL, "correct illegality");

  {
    for (int i = T_BOOLEAN; i <= T_CONFLICT; i++) {
      BasicType vt = (BasicType)i;
      BasicType ft = type2field[vt];
      switch (vt) {
      // the following types might plausibly show up in memory layouts:
      case T_BOOLEAN:
      case T_BYTE:
      case T_CHAR:
      case T_SHORT:
      case T_INT:
      case T_FLOAT:
      case T_DOUBLE:
      case T_LONG:
      case T_OBJECT:
      case T_ADDRESS:   // random raw pointer
      case T_CONFLICT:  // might as well support a bottom type
      case T_VOID:      // padding or other unaddressed word
	// layout type must map to itself
	assert(vt == ft, "");
	break;
      default:
	// non-layout type must map to a (different) layout type
	assert(vt != ft, "");
	assert(ft == type2field[ft], "");
      }
      // every type must map to same-sized layout type:
      assert(type2size[vt] == type2size[ft], "");
    }
  }
  // These are assumed, e.g., when filling HeapWords with juints.
  assert(is_power_of_2(sizeof(juint)), "juint must be power of 2");
  assert(is_power_of_2(HeapWordSize), "HeapWordSize must be power of 2");
  assert((size_t)HeapWordSize >= sizeof(juint),
         "HeapWord should be at least as large as juint");
  assert(sizeof(NULL) == sizeof(char*), "NULL must be same size as pointer");
#endif

  if( JavaPriority1_To_OSPriority != -1 )
    os::java_to_os_priority[1] = JavaPriority1_To_OSPriority;
  if( JavaPriority2_To_OSPriority != -1 )
    os::java_to_os_priority[2] = JavaPriority2_To_OSPriority;
  if( JavaPriority3_To_OSPriority != -1 )
    os::java_to_os_priority[3] = JavaPriority3_To_OSPriority;
  if( JavaPriority4_To_OSPriority != -1 )
    os::java_to_os_priority[4] = JavaPriority4_To_OSPriority;
  if( JavaPriority5_To_OSPriority != -1 )
    os::java_to_os_priority[5] = JavaPriority5_To_OSPriority;
  if( JavaPriority6_To_OSPriority != -1 )
    os::java_to_os_priority[6] = JavaPriority6_To_OSPriority;
  if( JavaPriority7_To_OSPriority != -1 )
    os::java_to_os_priority[7] = JavaPriority7_To_OSPriority;
  if( JavaPriority8_To_OSPriority != -1 )
    os::java_to_os_priority[8] = JavaPriority8_To_OSPriority;
  if( JavaPriority9_To_OSPriority != -1 )
    os::java_to_os_priority[9] = JavaPriority9_To_OSPriority;
  if(JavaPriority10_To_OSPriority != -1 )
    os::java_to_os_priority[10] = JavaPriority10_To_OSPriority;
}

const char* InliningFailureID2Name[IF_NUMMSGS] = {
"NO REASON",
"no failure",
"inlined intrinsic",
"general failure",
"polymorphic",
"polymorphic - no obvious winner",
"inline (hot)",
"too cold to inline",
"failed initial checks",
"size > DesiredMethodLimit",
"NodeCountInliningCutoff",
"not an accessor",
"inlining too deep",
"recursively inlining too deep",
"already compiled into a medium method",
"already compiled into a big method",
"hot method too big",
"too big",
"abstract method",
"method holder not initialized",
"native method",
"exception method",
"never executed",
"executed < MinInliningThreshold times",
"unloaded signature classes",
"compiler oracle request"
};

// Map BasicType to signature character
char type2char_tab[T_CONFLICT+1]={ 0, 0, 0, 0, 'Z', 'C', 'F', 'D', 'B', 'S', 'I', 'J', 'L', '[', 'V', 0, 0};

// Map BasicType to Java type name
const char* type2name_tab[T_CONFLICT+1] = {
  NULL, NULL, NULL, NULL,
  "boolean",
  "char",
  "float",
  "double",
  "byte",
  "short",
  "int",
  "long",
  "object",
  "array",
  "void",
  "*address*",
  "*conflict*"
};


BasicType name2type(const char* name) {
  for (int i = T_BOOLEAN; i <= T_VOID; i++) {
    BasicType t = (BasicType)i;
    if (type2name_tab[t] != NULL && 0 == strcmp(type2name_tab[t], name))
      return t;
  }
  return T_ILLEGAL;
}


// Map BasicType to size in words
int type2size[T_CONFLICT+1]={ -1, 0, 0, 0, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 0, 1, -1};

BasicType type2field[T_CONFLICT+1] = {
  (BasicType)0,            // 0,
  (BasicType)0,            // 1,
  (BasicType)0,            // 2,
  (BasicType)0,            // 3,
  T_BOOLEAN,     	   // T_BOOLEAN  =  4,
  T_CHAR,     	  	   // T_CHAR     =  5,
  T_FLOAT,   		   // T_FLOAT    =  6,
  T_DOUBLE,  		   // T_DOUBLE   =  7,
  T_BYTE,     		   // T_BYTE     =  8,
  T_SHORT,     		   // T_SHORT    =  9,
  T_INT,     		   // T_INT      = 10,
  T_LONG,    		   // T_LONG     = 11,
  T_OBJECT,                // T_OBJECT   = 12,
  T_OBJECT,                // T_ARRAY    = 13,
  T_VOID,                  // T_VOID     = 14,
  T_ADDRESS,               // T_ADDRESS  = 15,
  T_CONFLICT               // T_CONFLICT = 16,
};


BasicType type2wfield[T_CONFLICT+1] = {
  (BasicType)0,            // 0,
  (BasicType)0,            // 1,
  (BasicType)0,            // 2,
  (BasicType)0,            // 3,
  T_INT,     // T_BOOLEAN  =  4,
  T_INT,     // T_CHAR     =  5,
  T_FLOAT,   // T_FLOAT    =  6,
  T_DOUBLE,  // T_DOUBLE   =  7,
  T_INT,     // T_BYTE     =  8,
  T_INT,     // T_SHORT    =  9,
  T_INT,     // T_INT      = 10,
  T_LONG,    // T_LONG     = 11,
  T_OBJECT,  // T_OBJECT   = 12,
  T_OBJECT,  // T_ARRAY    = 13,
  T_VOID,    // T_VOID     = 14,
  T_ADDRESS, // T_ADDRESS  = 15,
  T_CONFLICT // T_CONFLICT = 16,
};


int type2aelembytes[T_CONFLICT+1] = {
  0,                      // 0
  0,                      // 1
  0,                      // 2
  0,                      // 3
  T_BOOLEAN_aelem_bytes,  // T_BOOLEAN  =  4,
  T_CHAR_aelem_bytes,     // T_CHAR     =  5,
  T_FLOAT_aelem_bytes,    // T_FLOAT    =  6,
  T_DOUBLE_aelem_bytes,   // T_DOUBLE   =  7,
  T_BYTE_aelem_bytes,     // T_BYTE     =  8,
  T_SHORT_aelem_bytes,    // T_SHORT    =  9,
  T_INT_aelem_bytes,      // T_INT      = 10,
  T_LONG_aelem_bytes,     // T_LONG     = 11,
  T_OBJECT_aelem_bytes,   // T_OBJECT   = 12,
  T_ARRAY_aelem_bytes,    // T_ARRAY    = 13,
  0,                      // T_VOID     = 14,
  T_INT_aelem_bytes,   	  // T_ADDRESS  = 15,	
  0                       // T_CONFLICT = 16,
};


int64_t type2logaelembytes[T_CONFLICT+1] = {
  -1,                      // 0
  -1,                      // 1
  -1,                      // 2
  -1,                      // 3
  exact_log2(T_BOOLEAN_aelem_bytes),  // T_BOOLEAN  =  4,
  exact_log2(T_CHAR_aelem_bytes),     // T_CHAR     =  5,
  exact_log2(T_FLOAT_aelem_bytes),    // T_FLOAT    =  6,
  exact_log2(T_DOUBLE_aelem_bytes),   // T_DOUBLE   =  7,
  exact_log2(T_BYTE_aelem_bytes),     // T_BYTE     =  8,
  exact_log2(T_SHORT_aelem_bytes),    // T_SHORT    =  9,
  exact_log2(T_INT_aelem_bytes),      // T_INT      = 10,
  exact_log2(T_LONG_aelem_bytes),     // T_LONG     = 11,
  exact_log2(T_OBJECT_aelem_bytes),   // T_OBJECT   = 12,
  exact_log2(T_ARRAY_aelem_bytes),    // T_ARRAY    = 13,
  -1,                                 // T_VOID     = 14,
  exact_log2(T_INT_aelem_bytes),      // T_ADDRESS  = 15,	
  -1                                  // T_CONFLICT = 16,
};


// Support for 64-bit integer arithmetic

// The following code is mostly taken from JVM typedefs_md.h and system_md.c

static const jlong  high_bit  = (jlong)1 << (jlong)63;
static const jlong other_bits = ~high_bit;

jlong float2long(jfloat f) {
  jlong tmp = (jlong) f;
  if (tmp != high_bit) {
    return tmp;
  } else {
    if (g_isnan((jdouble)f)) {
      return 0;
    }
    if (f < 0) {
      return high_bit;
    } else {
      return other_bits;
    }
  }
}


jlong double2long(jdouble f) {
  jlong tmp = (jlong) f;
  if (tmp != high_bit) {
    return tmp;
  } else {
    if (g_isnan(f)) {
      return 0;
    }
    if (f < 0) {
      return high_bit;
    } else {
      return other_bits;
    }
  }
}

// least common multiple
size_t lcm(size_t a, size_t b) {
    size_t cur, div, next;
   
    cur = MAX2(a, b); 
    div = MIN2(a, b);
    
    assert(div != 0, "lcm requires positive arguments");
    
    
    while ((next = cur % div) != 0) {
	cur = div; div = next;
    }
 
    
    julong result = julong(a) * b / div;
    assert(result <= (size_t)max_uintx, "Integer overflow in lcm");

    return size_t(result);
}
