<?php
/**
 * Created by PhpStorm.
 * User: John Kagga
 * Date: 8/2/2015
 * Time: 11:25 AM
 */

    /**
     * Shared interface for interactions
     * Interface Model
     */
    interface Model {

        /**
         * Load model from database
         * @param int $addressId
         * @return mixed
         */
        static function load ($addressId);

        /**
         * Save model
         * @return mixed
         */
        function save();
    }