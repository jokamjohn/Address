<?php
/**
 * Created by PhpStorm.
 * User: John Kagga
 * Date: 8/2/2015
 * Time: 4:37 PM
 */

    class ExceptionAddress extends Exception {

        public function __toString()
        {
            return __CLASS__.": [{$this->code}] : {$this->message}";
        }


    }