<?php
/**
 * Created by PhpStorm.
 * User: John Kagga
 * Date: 8/1/2015
 * Time: 6:45 PM
 */
require 'Constants.inc';
class Database {

    private $connection;
    //Store the single instance
    private static $_instance;

    /**
     * Get an instance of the database
     * @return Database
     */
    public static function getInstance(){
        //set instance if it does not exist
        if (!self::$_instance){
            self::$_instance =  new self();
        }
        return self::$_instance;
    }

    /**
     * Constructor
     */
    function __construct()
    {
        $this->connection = new mysqli('localhost',Constants::DB_USER,Constants::DB_PW,Constants::DB_NAME);
        //Error handling
        if(mysqli_connect_error()){
            trigger_error('Failed to connect to MYSQL: '.mysqli_connect_error(),E_USER_ERROR);
        }
    }

    /**
     * Empty clone method to prevent database duplication
     */
    function __clone()
    {

    }

    /**
     * Get the mysqli connection
     * @return mixed
     */
    public function getConnection(){
        return $this->connection;
    }

}