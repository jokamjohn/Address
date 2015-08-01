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

    /**
     * Magic __get
     * @param string $name
     * @return null
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