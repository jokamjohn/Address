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
class Address {

    //Address types
    public static $validAddressTypes = array(
        1 => 'Residence',
        2 => 'Business',
        3 => 'Park'
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
     * TODO Replace with database lookup
     * @return string
     */
    protected function _postal_code_guess(){
        return "LOOKUP";
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

}