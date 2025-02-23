/*
 * Copyright 2014-present MongoDB, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bson/bson.h"
#include "mongoc/mongoc.h"

#include <php.h>
#include <Zend/zend_interfaces.h>

#include "php_array_api.h"

#include "php_phongo.h"
#include "phongo_error.h"

#include "MongoDB/Server.h"
#include "MongoDB/WriteConcern.h"
#include "MongoDB/WriteConcernError.h"
#include "MongoDB/WriteError.h"

#define PHONGO_WRITERESULT_RETURN_LONG_FROM_BSON_INT32(iter, bson, key)                \
	if (bson_iter_init_find((iter), (bson), (key)) && BSON_ITER_HOLDS_INT32((iter))) { \
		RETURN_LONG(bson_iter_int32((iter)));                                          \
	}

zend_class_entry* php_phongo_writeresult_ce;

static bool php_phongo_writeresult_get_writeconcernerror(php_phongo_writeresult_t* intern, zval* return_value) /* {{{ */
{
	bson_iter_t iter, child;
	zval        writeconcernerror;

	ZVAL_NULL(return_value);

	if (bson_iter_init_find(&iter, intern->reply, "writeConcernErrors") && BSON_ITER_HOLDS_ARRAY(&iter) && bson_iter_recurse(&iter, &child)) {
		while (bson_iter_next(&child)) {
			bson_t         cbson;
			uint32_t       len;
			const uint8_t* data;

			if (!BSON_ITER_HOLDS_DOCUMENT(&child)) {
				continue;
			}

			bson_iter_document(&child, &len, &data);

			if (!bson_init_static(&cbson, data, len)) {
				continue;
			}

			if (!phongo_writeconcernerror_init(&writeconcernerror, &cbson)) {
				zval_ptr_dtor(&writeconcernerror);
				return false;
			}

			ZVAL_ZVAL(return_value, &writeconcernerror, 1, 1);

			return true;
		}
	}

	return true;
} /* }}} */

static bool php_phongo_writeresult_get_writeerrors(php_phongo_writeresult_t* intern, zval* return_value) /* {{{ */
{
	bson_iter_t iter, child;

	array_init(return_value);

	if (bson_iter_init_find(&iter, intern->reply, "writeErrors") && BSON_ITER_HOLDS_ARRAY(&iter) && bson_iter_recurse(&iter, &child)) {
		while (bson_iter_next(&child)) {
			bson_t         cbson;
			uint32_t       len;
			const uint8_t* data;
			zval           writeerror;

			if (!BSON_ITER_HOLDS_DOCUMENT(&child)) {
				continue;
			}

			bson_iter_document(&child, &len, &data);

			if (!bson_init_static(&cbson, data, len)) {
				continue;
			}

			if (!phongo_writeerror_init(&writeerror, &cbson)) {
				zval_ptr_dtor(&writeerror);
				continue;
			}

			add_next_index_zval(return_value, &writeerror);
		}
	}

	return true;
} /* }}} */

/* {{{ proto integer|null MongoDB\Driver\WriteResult::getInsertedCount()
   Returns the number of documents that were inserted */
static PHP_METHOD(WriteResult, getInsertedCount)
{
	zend_error_handling       error_handling;
	bson_iter_t               iter;
	php_phongo_writeresult_t* intern;

	intern = Z_WRITERESULT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	PHONGO_WRITERESULT_RETURN_LONG_FROM_BSON_INT32(&iter, intern->reply, "nInserted");
} /* }}} */

/* {{{ proto integer|null MongoDB\Driver\WriteResult::getMatchedCount()
   Returns the number of documents that matched the update criteria */
static PHP_METHOD(WriteResult, getMatchedCount)
{
	zend_error_handling       error_handling;
	bson_iter_t               iter;
	php_phongo_writeresult_t* intern;

	intern = Z_WRITERESULT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	PHONGO_WRITERESULT_RETURN_LONG_FROM_BSON_INT32(&iter, intern->reply, "nMatched");
} /* }}} */

/* {{{ proto integer|null MongoDB\Driver\WriteResult::getModifiedCount()
   Returns the number of documents that were actually modified by an update */
static PHP_METHOD(WriteResult, getModifiedCount)
{
	zend_error_handling       error_handling;
	bson_iter_t               iter;
	php_phongo_writeresult_t* intern;

	intern = Z_WRITERESULT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	PHONGO_WRITERESULT_RETURN_LONG_FROM_BSON_INT32(&iter, intern->reply, "nModified");
} /* }}} */

/* {{{ proto integer|null MongoDB\Driver\WriteResult::getDeletedCount()
   Returns the number of documents that were deleted */
static PHP_METHOD(WriteResult, getDeletedCount)
{
	zend_error_handling       error_handling;
	bson_iter_t               iter;
	php_phongo_writeresult_t* intern;

	intern = Z_WRITERESULT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	PHONGO_WRITERESULT_RETURN_LONG_FROM_BSON_INT32(&iter, intern->reply, "nRemoved");
} /* }}} */

/* {{{ proto integer|null MongoDB\Driver\WriteResult::getUpsertedCount()
   Returns the number of documents that were upserted */
static PHP_METHOD(WriteResult, getUpsertedCount)
{
	zend_error_handling       error_handling;
	bson_iter_t               iter;
	php_phongo_writeresult_t* intern;

	intern = Z_WRITERESULT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	PHONGO_WRITERESULT_RETURN_LONG_FROM_BSON_INT32(&iter, intern->reply, "nUpserted");
} /* }}} */

/* {{{ proto MongoDB\Driver\Server MongoDB\Driver\WriteResult::getServer()
   Returns the Server from which the result originated */
static PHP_METHOD(WriteResult, getServer)
{
	zend_error_handling       error_handling;
	php_phongo_writeresult_t* intern;

	intern = Z_WRITERESULT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	phongo_server_init(return_value, &intern->manager, intern->server_id);
} /* }}} */

/* {{{ proto array MongoDB\Driver\WriteResult::getUpsertedIds()
   Returns the identifiers generated by the server for upsert operations. */
static PHP_METHOD(WriteResult, getUpsertedIds)
{
	zend_error_handling       error_handling;
	bson_iter_t               iter, child;
	php_phongo_writeresult_t* intern;

	intern = Z_WRITERESULT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	array_init(return_value);

	if (bson_iter_init_find(&iter, intern->reply, "upserted") && BSON_ITER_HOLDS_ARRAY(&iter) && bson_iter_recurse(&iter, &child)) {
		while (bson_iter_next(&child)) {
			uint32_t              data_len;
			const uint8_t*        data = NULL;
			php_phongo_bson_state state;

			/* Use PHONGO_TYPEMAP_NATIVE_ARRAY for the root type so we can
			 * easily access the "index" and "_id" fields. */
			PHONGO_BSON_INIT_STATE(state);
			state.map.root_type = PHONGO_TYPEMAP_NATIVE_ARRAY;

			if (!BSON_ITER_HOLDS_DOCUMENT(&child)) {
				continue;
			}

			bson_iter_document(&child, &data_len, &data);

			if (php_phongo_bson_to_zval_ex(data, data_len, &state)) {
				zval* zid = php_array_fetchc(&state.zchild, "_id");
				add_index_zval(return_value, php_array_fetchc_long(&state.zchild, "index"), zid);
				zval_add_ref(zid);
			}

			zval_ptr_dtor(&state.zchild);
		}
	}
} /* }}} */

/* {{{ proto WriteConcernError MongoDB\Driver\WriteResult::getWriteConcernError()
   Return any write concern error that occurred */
static PHP_METHOD(WriteResult, getWriteConcernError)
{
	zend_error_handling       error_handling;
	php_phongo_writeresult_t* intern;

	intern = Z_WRITERESULT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	php_phongo_writeresult_get_writeconcernerror(intern, return_value);
} /* }}} */

/* {{{ proto WriteError[] MongoDB\Driver\WriteResult::getWriteErrors()
   Returns any write errors that occurred */
static PHP_METHOD(WriteResult, getWriteErrors)
{
	zend_error_handling       error_handling;
	php_phongo_writeresult_t* intern;

	intern = Z_WRITERESULT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	php_phongo_writeresult_get_writeerrors(intern, return_value);
} /* }}} */

/* {{{ proto boolean MongoDB\Driver\WriteResult::isAcknowledged()
   Returns whether the write operation was acknowledged (based on the write
   concern). */
static PHP_METHOD(WriteResult, isAcknowledged)
{
	zend_error_handling       error_handling;
	php_phongo_writeresult_t* intern;

	intern = Z_WRITERESULT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	RETURN_BOOL(mongoc_write_concern_is_acknowledged(intern->write_concern));
} /* }}} */

/* {{{ MongoDB\Driver\WriteResult function entries */
ZEND_BEGIN_ARG_INFO_EX(ai_WriteResult_void, 0, 0, 0)
ZEND_END_ARG_INFO()

static zend_function_entry php_phongo_writeresult_me[] = {
	/* clang-format off */
	PHP_ME(WriteResult, getInsertedCount, ai_WriteResult_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(WriteResult, getMatchedCount, ai_WriteResult_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(WriteResult, getModifiedCount, ai_WriteResult_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(WriteResult, getDeletedCount, ai_WriteResult_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(WriteResult, getUpsertedCount, ai_WriteResult_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(WriteResult, getServer, ai_WriteResult_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(WriteResult, getUpsertedIds, ai_WriteResult_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(WriteResult, getWriteConcernError, ai_WriteResult_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(WriteResult, getWriteErrors, ai_WriteResult_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(WriteResult, isAcknowledged, ai_WriteResult_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	ZEND_NAMED_ME(__construct, PHP_FN(MongoDB_disabled___construct), ai_WriteResult_void, ZEND_ACC_PRIVATE | ZEND_ACC_FINAL)
	ZEND_NAMED_ME(__wakeup, PHP_FN(MongoDB_disabled___wakeup), ai_WriteResult_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_FE_END
	/* clang-format on */
};
/* }}} */

/* {{{ MongoDB\Driver\WriteResult object handlers */
static zend_object_handlers php_phongo_handler_writeresult;

static void php_phongo_writeresult_free_object(zend_object* object) /* {{{ */
{
	php_phongo_writeresult_t* intern = Z_OBJ_WRITERESULT(object);

	zend_object_std_dtor(&intern->std);

	if (intern->reply) {
		bson_destroy(intern->reply);
	}

	if (intern->write_concern) {
		mongoc_write_concern_destroy(intern->write_concern);
	}

	if (!Z_ISUNDEF(intern->manager)) {
		zval_ptr_dtor(&intern->manager);
	}
} /* }}} */

static zend_object* php_phongo_writeresult_create_object(zend_class_entry* class_type) /* {{{ */
{
	php_phongo_writeresult_t* intern = zend_object_alloc(sizeof(php_phongo_writeresult_t), class_type);

	zend_object_std_init(&intern->std, class_type);
	object_properties_init(&intern->std, class_type);

	intern->std.handlers = &php_phongo_handler_writeresult;

	return &intern->std;
} /* }}} */

static HashTable* php_phongo_writeresult_get_debug_info(phongo_compat_object_handler_type* object, int* is_temp) /* {{{ */
{
	php_phongo_writeresult_t* intern;
	zval                      retval = ZVAL_STATIC_INIT;
	bson_iter_t               iter;

	intern   = Z_OBJ_WRITERESULT(PHONGO_COMPAT_GET_OBJ(object));
	*is_temp = 1;
	array_init_size(&retval, 9);

#define PHONGO_WRITERESULT_SCP(field)                                                         \
	if (bson_iter_init_find(&iter, intern->reply, (field)) && BSON_ITER_HOLDS_INT32(&iter)) { \
		ADD_ASSOC_LONG_EX(&retval, (field), bson_iter_int32(&iter));                          \
	} else {                                                                                  \
		ADD_ASSOC_NULL_EX(&retval, (field));                                                  \
	}

	PHONGO_WRITERESULT_SCP("nInserted");
	PHONGO_WRITERESULT_SCP("nMatched");
	PHONGO_WRITERESULT_SCP("nModified");
	PHONGO_WRITERESULT_SCP("nRemoved");
	PHONGO_WRITERESULT_SCP("nUpserted");
#undef PHONGO_WRITERESULT_SCP

	if (bson_iter_init_find(&iter, intern->reply, "upserted") && BSON_ITER_HOLDS_ARRAY(&iter)) {
		uint32_t              len;
		const uint8_t*        data;
		php_phongo_bson_state state;

		PHONGO_BSON_INIT_DEBUG_STATE(state);
		bson_iter_array(&iter, &len, &data);
		if (!php_phongo_bson_to_zval_ex(data, len, &state)) {
			zval_ptr_dtor(&state.zchild);
			goto done;
		}

		ADD_ASSOC_ZVAL_EX(&retval, "upsertedIds", &state.zchild);
	} else {
		zval upsertedIds;
		array_init(&upsertedIds);
		ADD_ASSOC_ZVAL_EX(&retval, "upsertedIds", &upsertedIds);
	}

	{
		zval writeerrors;

		php_phongo_writeresult_get_writeerrors(intern, &writeerrors);
		ADD_ASSOC_ZVAL_EX(&retval, "writeErrors", &writeerrors);
	}

	{
		zval writeconcernerror;

		php_phongo_writeresult_get_writeconcernerror(intern, &writeconcernerror);
		ADD_ASSOC_ZVAL_EX(&retval, "writeConcernError", &writeconcernerror);
	}

	if (intern->write_concern) {
		zval write_concern;

		phongo_writeconcern_init(&write_concern, intern->write_concern);
		ADD_ASSOC_ZVAL_EX(&retval, "writeConcern", &write_concern);
	} else {
		ADD_ASSOC_NULL_EX(&retval, "writeConcern");
	}

done:
	return Z_ARRVAL(retval);
} /* }}} */
/* }}} */

void php_phongo_writeresult_init_ce(INIT_FUNC_ARGS) /* {{{ */
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "MongoDB\\Driver", "WriteResult", php_phongo_writeresult_me);
	php_phongo_writeresult_ce                = zend_register_internal_class(&ce);
	php_phongo_writeresult_ce->create_object = php_phongo_writeresult_create_object;
	PHONGO_CE_FINAL(php_phongo_writeresult_ce);
	PHONGO_CE_DISABLE_SERIALIZATION(php_phongo_writeresult_ce);

	memcpy(&php_phongo_handler_writeresult, phongo_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_phongo_handler_writeresult.get_debug_info = php_phongo_writeresult_get_debug_info;
	php_phongo_handler_writeresult.free_obj       = php_phongo_writeresult_free_object;
	php_phongo_handler_writeresult.offset         = XtOffsetOf(php_phongo_writeresult_t, std);
} /* }}} */

php_phongo_writeresult_t* phongo_writeresult_init(zval* return_value, bson_t* reply, zval* manager, uint32_t server_id) /* {{{ */
{
	php_phongo_writeresult_t* writeresult;

	object_init_ex(return_value, php_phongo_writeresult_ce);

	writeresult            = Z_WRITERESULT_OBJ_P(return_value);
	writeresult->reply     = bson_copy(reply);
	writeresult->server_id = server_id;

	ZVAL_ZVAL(&writeresult->manager, manager, 1, 0);

	return writeresult;
} /* }}} */
