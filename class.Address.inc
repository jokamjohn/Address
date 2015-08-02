<?php
/**
 * Created by PhpStorm.
 * User: John Kagga
 * Date: 8/1/2015
 * Time: 12:11 PM
 */
/*
 * Physical Address
 */
abstract class Address implements Model{

    //constants
    const ADDRESS_TYPE_RESIDENCE = 1;
    const ADDRESS_TYPE_BUSINESS = 2;
    const ADDRESS_TYPE_PARK = 3;

    const ERROR_CODE_ROW_NOT_FOUND = 1000;

    //Address types
    public static $validAddressTypes = array(
        Address::ADDRESS_TYPE_RESIDENCE => 'Residence',
        Address::ADDRESS_TYPE_BUSINESS => 'Business',
        Address::ADDRESS_TYPE_PARK => 'Park'
    );

    //street address
    public $street_address_1;
    public $street_address_2;

    //Name of city
    public $city_name;

    //subdivison
    public $subdivision_name;

    //Name of subdivision
    protected $_postalCode;

    //Name of the country
    public $country_name;

    //Primary key of an Address
    protected $_address_id;

    //Address typeId
    protected $_address_type_id;

    //when the record was created and last updated
    protected $_timeCreated;
    protected $_timeUpdated;

    function __construct($data = array())
    {

        $this->_init();
        $this->_timeCreated = time();
        //Ensure the address can be populated
        if (!is_array($data)){
            trigger_error('Unable to construct address with a '.get_class($name));
        }
        //If there is at least one value populate the address
        if(count($data) > 0){
            foreach ($data as $name => $value){
                //special case for protected properties
                if (in_array($name,array(
                    'timeCreated',
                    'timeUpdated',
                    'address_id',
                    'address_type_id',
                ))){
                     $name = '_'.$name;
                }
                $this->$name = $value;
            }
        }
    }


    /**
     * Magic __get
     * @param string $name
     * @return mixed
     */
    function __get($name)
    {
        //postal code lookup if unset
        if(!$this->_postalCode){
            $this->_postalCode = $this->_postal_code_guess();
        }
        //Attempt to return protected property by name
        $protected_property_name = '_'.$name;
        if(property_exists($this,$protected_property_name)){
            return $this->$protected_property_name;
        }
        //unable to access property: trigger error
        trigger_error('Undefined property via __get'.$name);
        return null;
    }

    /**
     * Magic __set
     * @param string $name
     * @param string $value
     * @return mixed
     */
    function __set($name, $value)
    {
        //No need to set the address id, since its now automatic
        //Allow anything to change the value
        if('postalCode' == $name){
            $this->$name = $value;
            return;
        }
        //Unable to access property: trigger error
//        trigger_error('Undefined or unallowed property via __set()'.$name);
    }
    /**
     * Guess the postal code given the subdivision and city
     * @return string
     */
    protected function _postal_code_guess(){
        $db = Database::getInstance();
        $mysqli = $db->getConnection();

        $sql_query = 'SELECT postal_code';
        $sql_query .= ' FROM location';

        $city_name = $mysqli->real_escape_string($this->city_name);
        $sql_query .= ' WHERE city_name = " '.$city_name.'"';

        $subdivision_name = $mysqli->real_escape_string($this->subdivision_name);
        $sql_query .= ' AND subdivision_name = "'.$subdivision_name.'"';

        //prints the query statement
//        print_r($sql_query);

        $result = $mysqli->query($sql_query);

        //checks for the validity of the query, returns boolean
//        var_dump($result);

        if ($row = $result->fetch_assoc()){
            return $row['postal_code'];
        }
    }

    /**
     * magic __toString
     * @return string
     */
    function __toString()
    {
        //this is polymorphism
        return $this->display();
    }


    /**
     * Force extending classes to implement init method
     * Add function to the __construct method in Address class
     * @return mixed
     */
    abstract protected function _init();


    /**
     * Display an address in Html
     * @return string
     */
    function display(){
        $output= "";

        //Street address
        $output.= $this->street_address_1;
        $output.='<br/>';
        if($this->street_address_2){
            $output.=$this->street_address_2;
        }

        //city, subdivision, postal
        $output.='<br/>';
        $output.=$this->city_name.', '.$this->subdivision_name;
        $output.=', '.$this->_postalCode;

        //country
        $output.='<br/>';
        $output.=$this->country_name;
        return $output;
    }

    /**Determine if an address type is valid
     * @param int $addressId
     * @return bool
     */
    public static function isValidAddressTypeId ($addressId){
        return array_key_exists($addressId,self::$validAddressTypes);
    }

    /**
     * If valid set the address type
     * @param mixed $address_type_id
     */
    protected function _setAddressTypeId($address_type_id)
    {
        if(self ::isValidAddressTypeId($address_type_id)){
            $this->_address_type_id = $address_type_id;
        }
    }

    /**
     * load an address
     * This function prevents the children from saving in a different way (keyword final)
     * Children cannot override this method
     * @param int $addressId
     * @return mixed|void
     * @throws Exception
     */
    final public static function load($addressId){
        $db = Database::getInstance();
        $mysqli = $db->getConnection();

        $sql_query  = 'SELECT address.* ';
        $sql_query .= 'FROM address ';
        $sql_query .= 'WHERE address_id = "' . (int) $addressId . '" ';

        $result = $mysqli->query($sql_query);
//        print_r($result);
        if ($row = $result->fetch_assoc()) {
//            print_r($row);
           return self::getInstance($row['address_type_id'], $row);
        }
        throw new ExceptionAddress('Address not found',self::ERROR_CODE_ROW_NOT_FOUND);
    }

    /**
     * Given an addressTypeId, return an instance of that subclass
     * @param int $addressTypeId
     * @param array $data
     * @return mixed
     */
    final public static function getInstance($addressTypeId, $data=array()){
        $className = 'Address'.self::$validAddressTypes[$addressTypeId];
        return new $className($data);
    }

    /*
     * Save an Address
     */
    final public function save(){

    }


}