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
abstract class Address {

    //constants
    const ADDRESS_TYPE_RESIDENCE = 1;
    const ADDRESS_TYPE_BUSINESS = 2;
    const ADDRESS_TYPE_PARK = 3;

    //Address types
    public static $validAddressTypes = array(
        Address::ADDRESS_TYPE_RESIDENCE => 'Residence',
        Address::ADDRESS_TYPE_BUSINESS => 'Business',
        Address::ADDRESS_TYPE_PARK => 'Park'
    );

    //street address
    public $streetAddress1;
    public $streetAddress2;

    //Name of city
    public $cityName;

    //subdivison
    public $subdivision;

    //Name of subdivision
    protected $_postalCode;

    //Name of the country
    public $countryName;

    //Primary key of an Address
    protected $_addressId;

    //Address typeId
    protected $_address_type_id;

    //when the record was created and last updated
    protected $_timeCreated;
    protected $_timeUpdated;

    function __construct($data = array())
    {
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
        //Only set valid address type id
        if ('address_type_id' == $name){
            $this->_setAddressTypeId($value);
            return;
        }
        //Allow anything to change the value
        if('postalCode' == $name){
            $this->$name = $value;
            return;
        }
        //Unable to access property: trigger error
        trigger_error('Undefined or unallowed property via __set()'.$name);
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

        $city_name = $mysqli->real_escape_string($this->cityName);
        $sql_query .= ' WHERE city_name = " '.$city_name.'"';

        $subdivision_name = $mysqli->real_escape_string($this->subdivision);
        $sql_query .= ' AND subdivision_name = "'.$subdivision_name.'"';

        //prints the query statement
        print_r($sql_query);

        $result = $mysqli->query($sql_query);

        //checks for the validity of the query, returns boolean
        var_dump($result);

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
     * Display an address in Html
     * @return string
     */
    function display(){
        $output= "";

        //Street address
        $output.= $this->streetAddress1;
        $output.='<br/>';
        if($this->streetAddress2){
            $output.=$this->streetAddress2;
        }

        //city, subdivision, postal
        $output.='<br/>';
        $output.=$this->cityName.', '.$this->subdivision;
        $output.=', '.$this->postalCode;

        //country
        $output.='<br/>';
        $output.=$this->countryName;
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



}