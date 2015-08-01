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
    public $postalCode;

    //Name of the country
    public $countryName;

    //Primary key of an Address
    protected $_addressId;

    //when the record was created and last updated
    protected $_timeCreated;
    protected $_timeUpdated;

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