/*
 * Copyright 2016-present MongoDB, Inc.
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

#include <php.h>
#include <Zend/zend_interfaces.h>

#include "php_phongo.h"
#include "phongo_bson_encode.h"
#include "phongo_error.h"

#include "BSON/ObjectId.h"
#include "MongoDB/Server.h"

zend_class_entry* php_phongo_commandsucceededevent_ce;

/* {{{ proto string CommandSucceededEvent::getCommandName()
   Returns the command name for this event */
PHP_METHOD(CommandSucceededEvent, getCommandName)
{
	zend_error_handling                 error_handling;
	php_phongo_commandsucceededevent_t* intern;

	intern = Z_COMMANDSUCCEEDEDEVENT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	RETVAL_STRING(intern->command_name);
} /* }}} */

/* {{{ proto int CommandSucceededEvent::getDurationMicros()
   Returns the event's duration in microseconds */
PHP_METHOD(CommandSucceededEvent, getDurationMicros)
{
	zend_error_handling                 error_handling;
	php_phongo_commandsucceededevent_t* intern;

	intern = Z_COMMANDSUCCEEDEDEVENT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	RETURN_LONG(intern->duration_micros);
} /* }}} */

/* {{{ proto string CommandSucceededEvent::getOperationId()
   Returns the event's operation ID */
PHP_METHOD(CommandSucceededEvent, getOperationId)
{
	zend_error_handling                 error_handling;
	php_phongo_commandsucceededevent_t* intern;
	char                                int_as_string[20];

	intern = Z_COMMANDSUCCEEDEDEVENT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	sprintf(int_as_string, "%" PRIu64, intern->operation_id);
	RETVAL_STRING(int_as_string);
} /* }}} */

/* {{{ proto stdClass CommandSucceededEvent::getReply()
   Returns the reply document associated with the event */
PHP_METHOD(CommandSucceededEvent, getReply)
{
	zend_error_handling                 error_handling;
	php_phongo_commandsucceededevent_t* intern;
	php_phongo_bson_state               state;

	PHONGO_BSON_INIT_STATE(state);

	intern = Z_COMMANDSUCCEEDEDEVENT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	if (!php_phongo_bson_to_zval_ex(bson_get_data(intern->reply), intern->reply->len, &state)) {
		zval_ptr_dtor(&state.zchild);
		return;
	}

	RETURN_ZVAL(&state.zchild, 0, 1);
} /* }}} */

/* {{{ proto string CommandsucceededEvent::getRequestId()
   Returns the event's request ID */
PHP_METHOD(CommandSucceededEvent, getRequestId)
{
	zend_error_handling                 error_handling;
	php_phongo_commandsucceededevent_t* intern;
	char                                int_as_string[20];

	intern = Z_COMMANDSUCCEEDEDEVENT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	sprintf(int_as_string, "%" PRIu64, intern->request_id);
	RETVAL_STRING(int_as_string);
} /* }}} */

/* {{{ proto MongoDB\Driver\Server CommandSucceededEvent::getServer()
   Returns the Server from which the event originated */
PHP_METHOD(CommandSucceededEvent, getServer)
{
	zend_error_handling                 error_handling;
	php_phongo_commandsucceededevent_t* intern;

	intern = Z_COMMANDSUCCEEDEDEVENT_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	phongo_server_init(return_value, &intern->manager, intern->server_id);
} /* }}} */

/* {{{ proto MongoDB\BSON\ObjectId|null CommandSucceededEvent::getServiceId()
   Returns the event's service ID */
PHP_METHOD(CommandSucceededEvent, getServiceId)
{
	php_phongo_commandsucceededevent_t* intern = Z_COMMANDSUCCEEDEDEVENT_OBJ_P(getThis());

	PHONGO_PARSE_PARAMETERS_NONE();

	if (!intern->has_service_id) {
		RETURN_NULL();
	}

	phongo_objectid_init(return_value, &intern->service_id);
} /* }}} */

/* {{{ proto int|null CommandSucceededEvent::getServerConnectionId()
   Returns the event's server connection ID */
PHP_METHOD(CommandSucceededEvent, getServerConnectionId)
{
	php_phongo_commandsucceededevent_t* intern = Z_COMMANDSUCCEEDEDEVENT_OBJ_P(getThis());

	PHONGO_PARSE_PARAMETERS_NONE();

	/* TODO: Use MONGOC_NO_SERVER_CONNECTION_ID once it is added to libmongoc's public API (CDRIVER-4176) */
	if (intern->server_connection_id == -1) {
		RETURN_NULL();
	}

	RETURN_LONG(intern->server_connection_id);
} /* }}} */

/**
 * Event thrown when a command has succeeded to execute.
 *
 * This class is only constructed internally.
 */

/* {{{ MongoDB\Driver\Monitoring\CommandSucceededEvent function entries */
ZEND_BEGIN_ARG_INFO_EX(ai_CommandSucceededEvent_void, 0, 0, 0)
ZEND_END_ARG_INFO()

static zend_function_entry php_phongo_commandsucceededevent_me[] = {
	/* clang-format off */
	ZEND_NAMED_ME(__construct, PHP_FN(MongoDB_disabled___construct), ai_CommandSucceededEvent_void, ZEND_ACC_PRIVATE | ZEND_ACC_FINAL)
	PHP_ME(CommandSucceededEvent, getCommandName, ai_CommandSucceededEvent_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(CommandSucceededEvent, getDurationMicros, ai_CommandSucceededEvent_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(CommandSucceededEvent, getOperationId, ai_CommandSucceededEvent_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(CommandSucceededEvent, getReply, ai_CommandSucceededEvent_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(CommandSucceededEvent, getRequestId, ai_CommandSucceededEvent_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(CommandSucceededEvent, getServer, ai_CommandSucceededEvent_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(CommandSucceededEvent, getServiceId, ai_CommandSucceededEvent_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_ME(CommandSucceededEvent, getServerConnectionId, ai_CommandSucceededEvent_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	ZEND_NAMED_ME(__wakeup, PHP_FN(MongoDB_disabled___wakeup), ai_CommandSucceededEvent_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_FE_END
	/* clang-format on */
};
/* }}} */

/* {{{ MongoDB\Driver\Monitoring\CommandSucceededEvent object handlers */
static zend_object_handlers php_phongo_handler_commandsucceededevent;

static void php_phongo_commandsucceededevent_free_object(zend_object* object) /* {{{ */
{
	php_phongo_commandsucceededevent_t* intern = Z_OBJ_COMMANDSUCCEEDEDEVENT(object);

	zend_object_std_dtor(&intern->std);

	if (!Z_ISUNDEF(intern->manager)) {
		zval_ptr_dtor(&intern->manager);
	}

	if (intern->reply) {
		bson_destroy(intern->reply);
	}

	if (intern->command_name) {
		efree(intern->command_name);
	}
} /* }}} */

static zend_object* php_phongo_commandsucceededevent_create_object(zend_class_entry* class_type) /* {{{ */
{
	php_phongo_commandsucceededevent_t* intern = zend_object_alloc(sizeof(php_phongo_commandsucceededevent_t), class_type);

	zend_object_std_init(&intern->std, class_type);
	object_properties_init(&intern->std, class_type);

	intern->std.handlers = &php_phongo_handler_commandsucceededevent;

	return &intern->std;
} /* }}} */

static HashTable* php_phongo_commandsucceededevent_get_debug_info(phongo_compat_object_handler_type* object, int* is_temp) /* {{{ */
{
	php_phongo_commandsucceededevent_t* intern;
	zval                                retval = ZVAL_STATIC_INIT;
	char                                operation_id[20], request_id[20];
	php_phongo_bson_state               reply_state;

	PHONGO_BSON_INIT_STATE(reply_state);

	intern   = Z_OBJ_COMMANDSUCCEEDEDEVENT(PHONGO_COMPAT_GET_OBJ(object));
	*is_temp = 1;
	array_init_size(&retval, 6);

	ADD_ASSOC_STRING(&retval, "commandName", intern->command_name);
	ADD_ASSOC_INT64(&retval, "durationMicros", (int64_t) intern->duration_micros);

	sprintf(operation_id, "%" PRIu64, intern->operation_id);
	ADD_ASSOC_STRING(&retval, "operationId", operation_id);

	if (!php_phongo_bson_to_zval_ex(bson_get_data(intern->reply), intern->reply->len, &reply_state)) {
		zval_ptr_dtor(&reply_state.zchild);
		goto done;
	}

	ADD_ASSOC_ZVAL(&retval, "reply", &reply_state.zchild);

	sprintf(request_id, "%" PRIu64, intern->request_id);
	ADD_ASSOC_STRING(&retval, "requestId", request_id);

	{
		zval server;

		phongo_server_init(&server, &intern->manager, intern->server_id);
		ADD_ASSOC_ZVAL_EX(&retval, "server", &server);
	}

	if (intern->has_service_id) {
		zval service_id;

		phongo_objectid_init(&service_id, &intern->service_id);
		ADD_ASSOC_ZVAL_EX(&retval, "serviceId", &service_id);
	} else {
		ADD_ASSOC_NULL_EX(&retval, "serviceId");
	}

	/* TODO: Use MONGOC_NO_SERVER_CONNECTION_ID once it is added to libmongoc's public API (CDRIVER-4176) */
	if (intern->server_connection_id == -1) {
		ADD_ASSOC_NULL_EX(&retval, "serverConnectionId");
	} else {
		ADD_ASSOC_LONG_EX(&retval, "serverConnectionId", intern->server_connection_id);
	}

done:
	return Z_ARRVAL(retval);
} /* }}} */
/* }}} */

void php_phongo_commandsucceededevent_init_ce(INIT_FUNC_ARGS) /* {{{ */
{
	zend_class_entry ce;
	(void) type;
	(void) module_number;

	INIT_NS_CLASS_ENTRY(ce, "MongoDB\\Driver\\Monitoring", "CommandSucceededEvent", php_phongo_commandsucceededevent_me);
	php_phongo_commandsucceededevent_ce                = zend_register_internal_class(&ce);
	php_phongo_commandsucceededevent_ce->create_object = php_phongo_commandsucceededevent_create_object;
	PHONGO_CE_FINAL(php_phongo_commandsucceededevent_ce);
	PHONGO_CE_DISABLE_SERIALIZATION(php_phongo_commandsucceededevent_ce);

	memcpy(&php_phongo_handler_commandsucceededevent, phongo_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_phongo_handler_commandsucceededevent.get_debug_info = php_phongo_commandsucceededevent_get_debug_info;
	php_phongo_handler_commandsucceededevent.free_obj       = php_phongo_commandsucceededevent_free_object;
	php_phongo_handler_commandsucceededevent.offset         = XtOffsetOf(php_phongo_commandsucceededevent_t, std);

	return;
} /* }}} */
