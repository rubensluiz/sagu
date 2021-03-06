<?php

class PostgresConnection extends MConnection
{
    public function __construct($conf)
    {
        parent::__construct($conf);
    }

    public function _connect($dbhost, $loginDB, $loginUID, $loginPWD, $persistent=TRUE, $parameters=NULL, $port=NULL)
    {
        $h = explode(':',$dbhost);
        $host       = $h[0];
        
        if ( !$port )
        {
            $port = is_null($h[1]) ? '5432' : $h[1];
        }

        $arg = "host=$host " . ($loginDB ? "dbname=$loginDB " : "") . "port=$port " . "user=$loginUID " . "password=$loginPWD";

        if (false && $persistent)
        {
            $this->id = pg_pconnect($arg);
        }
        else
        {
            $this->id = pg_connect($arg);
        }
        $encoding = ($enc = $this->_miolo->getConf('options.charset')) != '' ? $enc : 'ISO-8859-1';
        pg_query($this->id, "SET CLIENT_ENCODING TO '{$encoding}'");
    }

    public function _close()
    {
        pg_close($this->id);
    }

    public function _error($resource = null)
    {
        return $this->getErrorField($resource ? $resource : $this->id);
    }

    public function _execute($sql)
    {
        pg_send_query($this->id, $sql);
        $rs = pg_get_result($this->id);

        $this->throwError($rs);

        $success = false;

        if ($rs)
        {
            $success = true;
            $this->affectedrows = pg_affected_rows($rs);
            pg_free_result($rs);
        }
        else
        {
            $this->traceback[] = pg_last_error($this->id);
        }

        return $success;
    }

    /**
     * @return PostgresQuery Database query object.
     */
    public function _createquery()
    {
        return new PostgresQuery();
    }

    public function _chartotimestamp($timestamp,  $format='DD/MM/YYYY HH24:MI:SS')
    {
        return ":TO_TIMESTAMP('" . $timestamp . "','$format') ";
    }

    public function _chartodate($date, $format='DD/MM/YYYY')
    {
        return ":TO_DATE('" . $date . "','$format') ";
    }

    public function _timestamptochar($timestamp,  $format='DD/MM/YYYY HH24:MI:SS')
    {
        return "TO_CHAR(" . $timestamp . ",'$format') ";
    }

    public function _datetochar($date,  $format='DD/MM/YYYY')
    {
        return "TO_CHAR(" . $date . ",'$format') ";
    }

    /**
     * Check Postgres errors and throw the appropriate exception
     * All the error codes can be found at http://www.postgresql.org/docs/8.4/static/errcodes-appendix.html
     */
    public function throwError($result)
    {
        switch ( $this->getErrorField($result, PGSQL_DIAG_SQLSTATE) )
        {
            // Class 00 - Successful Completion
            case '00000': // SUCCESSFUL COMPLETION
                // throw nothing
                break;

            // Class 01 ? Warning
            case '01000': // WARNING
            case '0100C': // DYNAMIC RESULT SETS RETURNED
            case '01008': // IMPLICIT ZERO BIT PADDING
            case '01003': // NULL VALUE ELIMINATED IN SET FUNCTION
            case '01007': // PRIVILEGE NOT GRANTED
            case '01006': // PRIVILEGE NOT REVOKED
            case '01004': // STRING DATA RIGHT TRUNCATION
            case '01P01': // DEPRECATED FEATURE
                // throw nothing
                break;

            // Class 02 ? No Data (this is also a warning class per the SQL standard)
            case '02000': // NO DATA
            case '02001': // NO ADDITIONAL DYNAMIC RESULT SETS RETURNED
                // throw nothing
                break;

            // Class 03 ? SQL Statement Not Yet Complete
            case '03000': // SQL STATEMENT NOT YET COMPLETE
                // throw nothing
                break;

            // Class 08 ? Connection Exception
            case '08000': // CONNECTION EXCEPTION
            case '08003': // CONNECTION DOES NOT EXIST
            case '08006': // CONNECTION FAILURE
            case '08001': // SQLCLIENT UNABLE TO ESTABLISH SQLCONNECTION
            case '08004': // SQLSERVER REJECTED ESTABLISHMENT OF SQLCONNECTION
            case '08007': // TRANSACTION RESOLUTION UNKNOWN
            case '08P01': // PROTOCOL VIOLATION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 09 ? Triggered Action Exception
            case '09000': // TRIGGERED ACTION EXCEPTION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 0A ? Feature Not Supported
            case '0A000': // FEATURE NOT SUPPORTED
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 0B ? Invalid Transaction Initiation
            case '0B000': // INVALID TRANSACTION INITIATION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 0F ? Locator Exception
            case '0F000': // LOCATOR EXCEPTION
            case '0F001': // INVALID LOCATOR SPECIFICATION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 0L ? Invalid Grantor
            case '0L000': // INVALID GRANTOR
            case '0LP01': // INVALID GRANT OPERATION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 0P ? Invalid Role Specification
            case '0P000': // INVALID ROLE SPECIFICATION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 21 ? Cardinality Violation
            case '21000': // CARDINALITY VIOLATION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 22 ? Data Exception
            case '22000': // DATA EXCEPTION
            case '2202E': // ARRAY SUBSCRIPT ERROR
            case '22021': // CHARACTER NOT IN REPERTOIRE
            case '22008': // DATETIME FIELD OVERFLOW
            case '22012': // DIVISION BY ZERO
            case '22005': // ERROR IN ASSIGNMENT
            case '2200B': // ESCAPE CHARACTER CONFLICT
            case '22022': // INDICATOR OVERFLOW
            case '22015': // INTERVAL FIELD OVERFLOW
            case '2201E': // INVALID ARGUMENT FOR LOGARITHM
            case '2201F': // INVALID ARGUMENT FOR POWER FUNCTION
            case '2201G': // INVALID ARGUMENT FOR WIDTH BUCKET FUNCTION
            case '22018': // INVALID CHARACTER VALUE FOR CAST
            case '22007': // INVALID DATETIME FORMAT
            case '22019': // INVALID ESCAPE CHARACTER
            case '2200D': // INVALID ESCAPE OCTET
            case '22025': // INVALID ESCAPE SEQUENCE
            case '22P06': // NONSTANDARD USE OF ESCAPE CHARACTER
            case '22010': // INVALID INDICATOR PARAMETER VALUE
            case '22020': // INVALID LIMIT VALUE
            case '22023': // INVALID PARAMETER VALUE
            case '2201B': // INVALID REGULAR EXPRESSION
            case '22009': // INVALID TIME ZONE DISPLACEMENT VALUE
            case '2200C': // INVALID USE OF ESCAPE CHARACTER
            case '2200G': // MOST SPECIFIC TYPE MISMATCH
            case '22004': // NULL VALUE NOT ALLOWED
            case '22002': // NULL VALUE NO INDICATOR PARAMETER
            case '22003': // NUMERIC VALUE OUT OF RANGE
            case '22026': // STRING DATA LENGTH MISMATCH
            case '22001': // STRING DATA RIGHT TRUNCATION
            case '22011': // SUBSTRING ERROR
            case '22027': // TRIM ERROR
            case '22024': // UNTERMINATED C STRING
            case '2200F': // ZERO LENGTH CHARACTER STRING
            case '22P01': // FLOATING POINT EXCEPTION
            case '22P02': // INVALID TEXT REPRESENTATION
            case '22P03': // INVALID BINARY REPRESENTATION
            case '22P04': // BAD COPY FILE FORMAT
            case '22P05': // UNTRANSLATABLE CHARACTER
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 23 ? Integrity Constraint Violation
            case '23000': // INTEGRITY CONSTRAINT VIOLATION
            case '23001': // RESTRICT VIOLATION
            case '23502': // NOT NULL VIOLATION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            case '23503': // FOREIGN KEY VIOLATION

                preg_match_all('/\"[^"]*\"/', $this->getErrorField($result), $messageData);

                $messageData = $messageData[0];

                // If there is a third quoted string in the messsage, it's a delete operation
                if ( $messageData[2] )
                {
                    $table = trim($messageData[0], '"');
                    $fkTable = trim($messageData[2], '"');
                    $message = _M('@1 references @2. It cannot be removed.', NULL, $fkTable, $table);
                }
                // Else it's an insert or an update
                else
                {
                    // Get the message detail to know which table has the absent reference
                    preg_match_all('/\"[^"]*\"/', $this->getErrorField(PGSQL_DIAG_MESSAGE_DETAIL), $messageData);

                    $table = trim($messageData[0][0], '"');
                    $message = _M('Reference is invalid @1', NULL, $table);
                }

                throw new MDatabaseException($message, MDatabaseException::KNOWN_ERROR_CODE);
                break;


            case '23505': // UNIQUE VIOLATION

                $message = _M('The identifier already exists on database');

                throw new MDatabaseException($message, MDatabaseException::KNOWN_ERROR_CODE);
                break;


            case '23514': // CHECK VIOLATION

                // Get the error message to know which table has the business rule
                preg_match_all('/\"[^"]*\"/', $this->getErrorField($result), $messageData);

                $table = trim($messageData[0][0], '"');
                $message = _M('Operation violates check constraint at table @1', NULL, $table);

                throw new MDatabaseException($message, MDatabaseException::KNOWN_ERROR_CODE);
                break;


            // Class 24 ? Invalid Cursor State
            case '24000': // INVALID CURSOR STATE
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 25 ? Invalid Transaction State
            case '25000': // INVALID TRANSACTION STATE
            case '25001': // ACTIVE SQL TRANSACTION
            case '25002': // BRANCH TRANSACTION ALREADY ACTIVE
            case '25008': // HELD CURSOR REQUIRES SAME ISOLATION LEVEL
            case '25003': // INAPPROPRIATE ACCESS MODE FOR BRANCH TRANSACTION
            case '25004': // INAPPROPRIATE ISOLATION LEVEL FOR BRANCH TRANSACTION
            case '25005': // NO ACTIVE SQL TRANSACTION FOR BRANCH TRANSACTION
            case '25006': // READ ONLY SQL TRANSACTION
            case '25007': // SCHEMA AND DATA STATEMENT MIXING NOT SUPPORTED
            case '25P01': // NO ACTIVE SQL TRANSACTION
            case '25P02': // IN FAILED SQL TRANSACTION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 26 ? Invalid SQL Statement Name
            case '26000': // INVALID SQL STATEMENT NAME
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 27 ? Triggered Data Change Violation
            case '27000': // TRIGGERED DATA CHANGE VIOLATION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 28 ? Invalid Authorization Specification
            case '28000': // INVALID AUTHORIZATION SPECIFICATION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 2B ? Dependent Privilege Descriptors Still Exist
            case '2B000': // DEPENDENT PRIVILEGE DESCRIPTORS STILL EXIST
            case '2BP01': // DEPENDENT OBJECTS STILL EXIST
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 2D ? Invalid Transaction Termination
            case '2D000': // INVALID TRANSACTION TERMINATION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 2F ? SQL Routine Exception
            case '2F000': // SQL ROUTINE EXCEPTION
            case '2F005': // FUNCTION EXECUTED NO RETURN STATEMENT
            case '2F002': // MODIFYING SQL DATA NOT PERMITTED
            case '2F003': // PROHIBITED SQL STATEMENT ATTEMPTED
            case '2F004': // READING SQL DATA NOT PERMITTED
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 34 ? Invalid Cursor Name
            case '34000': // INVALID CURSOR NAME
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 38 ? External Routine Exception
            case '38000': // EXTERNAL ROUTINE EXCEPTION
            case '38001': // CONTAINING SQL NOT PERMITTED
            case '38002': // MODIFYING SQL DATA NOT PERMITTED
            case '38003': // PROHIBITED SQL STATEMENT ATTEMPTED
            case '38004': // READING SQL DATA NOT PERMITTED
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 39 ? External Routine Invocation Exception
            case '39000': // EXTERNAL ROUTINE INVOCATION EXCEPTION
            case '39001': // INVALID SQLSTATE RETURNED
            case '39004': // NULL VALUE NOT ALLOWED
            case '39P01': // TRIGGER PROTOCOL VIOLATED
            case '39P02': // SRF PROTOCOL VIOLATED
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 3B ? Savepoint Exception
            case '3B000': // SAVEPOINT EXCEPTION
            case '3B001': // INVALID SAVEPOINT SPECIFICATION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 3D ? Invalid Catalog Name
            case '3D000': // INVALID CATALOG NAME
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 3F ? Invalid Schema Name
            case '3F000': // INVALID SCHEMA NAME
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 40 ? Transaction Rollback
            case '40000': // TRANSACTION ROLLBACK
            case '40002': // TRANSACTION INTEGRITY CONSTRAINT VIOLATION
            case '40001': // SERIALIZATION FAILURE
            case '40003': // STATEMENT COMPLETION UNKNOWN
            case '40P01': // DEADLOCK DETECTED
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 42 ? Syntax Error or Access Rule Violation
            case '42000': // SYNTAX ERROR OR ACCESS RULE VIOLATION
            case '42601': // SYNTAX ERROR
            case '42501': // INSUFFICIENT PRIVILEGE
            case '42846': // CANNOT COERCE
            case '42803': // GROUPING ERROR
            case '42830': // INVALID FOREIGN KEY
            case '42602': // INVALID NAME
            case '42622': // NAME TOO LONG
            case '42939': // RESERVED NAME
            case '42804': // DATATYPE MISMATCH
            case '42P18': // INDETERMINATE DATATYPE
            case '42809': // WRONG OBJECT TYPE
            case '42703': // UNDEFINED COLUMN
            case '42883': // UNDEFINED FUNCTION
            case '42P01': // UNDEFINED TABLE
            case '42P02': // UNDEFINED PARAMETER
            case '42704': // UNDEFINED OBJECT
            case '42701': // DUPLICATE COLUMN
            case '42P03': // DUPLICATE CURSOR
            case '42P04': // DUPLICATE DATABASE
            case '42723': // DUPLICATE FUNCTION
            case '42P05': // DUPLICATE PREPARED STATEMENT
            case '42P06': // DUPLICATE SCHEMA
            case '42P07': // DUPLICATE TABLE
            case '42712': // DUPLICATE ALIAS
            case '42710': // DUPLICATE OBJECT
            case '42702': // AMBIGUOUS COLUMN
            case '42725': // AMBIGUOUS FUNCTION
            case '42P08': // AMBIGUOUS PARAMETER
            case '42P09': // AMBIGUOUS ALIAS
            case '42P10': // INVALID COLUMN REFERENCE
            case '42611': // INVALID COLUMN DEFINITION
            case '42P11': // INVALID CURSOR DEFINITION
            case '42P12': // INVALID DATABASE DEFINITION
            case '42P13': // INVALID FUNCTION DEFINITION
            case '42P14': // INVALID PREPARED STATEMENT DEFINITION
            case '42P15': // INVALID SCHEMA DEFINITION
            case '42P16': // INVALID TABLE DEFINITION
            case '42P17': // INVALID OBJECT DEFINITION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 44 ? WITH CHECK OPTION Violation
            case '44000': // WITH CHECK OPTION VIOLATION
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 53 ? Insufficient Resources
            case '53000': // INSUFFICIENT RESOURCES
            case '53100': // DISK FULL
            case '53200': // OUT OF MEMORY
            case '53300': // TOO MANY CONNECTIONS
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 54 ? Program Limit Exceeded
            case '54000': // PROGRAM LIMIT EXCEEDED
            case '54001': // STATEMENT TOO COMPLEX
            case '54011': // TOO MANY COLUMNS
            case '54023': // TOO MANY ARGUMENTS
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 55 ? Object Not In Prerequisite State
            case '55000': // OBJECT NOT IN PREREQUISITE STATE
            case '55006': // OBJECT IN USE
            case '55P02': // CANT CHANGE RUNTIME PARAM
            case '55P03': // LOCK NOT AVAILABLE
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 57 ? Operator Intervention
            case '57000': // OPERATOR INTERVENTION
            case '57014': // QUERY CANCELED
            case '57P01': // ADMIN SHUTDOWN
            case '57P02': // CRASH SHUTDOWN
            case '57P03': // CANNOT CONNECT NOW
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class 58 ? System Error (errors external to PostgreSQL itself)
            case '58030': // IO ERROR
            case '58P01': // UNDEFINED FILE
            case '58P02': // DUPLICATE FILE
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class F0 ? Configuration File Error
            case 'F0000': // CONFIG FILE ERROR
            case 'F0001': // LOCK FILE EXISTS
                throw new MDatabaseException($this->getErrorField($result));
                break;

            // Class P0 ? PL/pgSQL Error
            case 'P0000': // PLPGSQL ERROR
                throw new MDatabaseException($this->getErrorField($result));
                break;

            case 'P0001': // RAISE EXCEPTION
                throw new MDatabaseException($this->getErrorField($result), MDatabaseException::KNOWN_ERROR_CODE);
                break;

            // Class XX ? Internal Error
            case 'XX000': // INTERNAL ERROR
            case 'XX001': // DATA CORRUPTED
            case 'XX002': // INDEX CORRUPTED
                throw new MDatabaseException($this->getErrorField($result));
                break;
        }
    }

    /**
     * Get database error message according to the given postgres constant
     * http://php.net/manual/en/function.pg-result-error-field.php
     *
     * @param string $fieldcode The error field identifier
     * @return string A detailed error message of the given field
     */
    public function getErrorField($result, $fieldcode = PGSQL_DIAG_MESSAGE_PRIMARY)
    {
        return pg_result_error_field($result, $fieldcode);
    }
}
?>
