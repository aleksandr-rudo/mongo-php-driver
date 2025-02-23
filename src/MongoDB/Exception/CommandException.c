/*
 * Copyright 2018-present MongoDB, Inc.
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

#include <php.h>

#include "php_phongo.h"
#include "phongo_error.h"

zend_class_entry* php_phongo_commandexception_ce;

/* {{{ proto document MongoDB\Driver\Exception\CommandException::getResultDocument()
   Returns the result document from the failed command. */
static PHP_METHOD(CommandException, getResultDocument)
{
	zend_error_handling error_handling;
	zval*               resultdocument;
	zval                rv;

	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	resultdocument = zend_read_property(php_phongo_commandexception_ce, PHONGO_COMPAT_OBJ_P(getThis()), ZEND_STRL("resultDocument"), 0, &rv);

	RETURN_ZVAL(resultdocument, 1, 0);
} /* }}} */

/* {{{ MongoDB\Driver\Exception\CommandException function entries */
ZEND_BEGIN_ARG_INFO_EX(ai_CommandException_void, 0, 0, 0)
ZEND_END_ARG_INFO()

static zend_function_entry php_phongo_commandexception_me[] = {
	/* clang-format off */
	PHP_ME(CommandException, getResultDocument, ai_CommandException_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_FE_END
	/* clang-format on */
};
/* }}} */

void php_phongo_commandexception_init_ce(INIT_FUNC_ARGS) /* {{{ */
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "MongoDB\\Driver\\Exception", "CommandException", php_phongo_commandexception_me);
	php_phongo_commandexception_ce = zend_register_internal_class_ex(&ce, php_phongo_serverexception_ce);

	zend_declare_property_null(php_phongo_commandexception_ce, ZEND_STRL("resultDocument"), ZEND_ACC_PROTECTED);
} /* }}} */
