<?php
/**
 * Created by PhpStorm.
 * User: John Kagga
 * Date: 8/2/2015
 * Time: 10:27 AM
 */


    /**
     * Park Address
     * Class AddressPark
     */
    class AddressPark extends Address {

//    /**
//     * Overriding the country in Address
//     * @var string
//     */
//    public $countryName = 'Uganda';


        /**
         * Overriding the parent method
         * @return string
         */
        function display()
        {
            $output = '<div style="background-color: brown">';
            $output .= parent::display();
            $output .= '</div>';
            return $output;
        }



        /**
     * Force extending classes to implement init method
     * Add function to the __construct method
     * @return mixed
     */
    protected function _init()
    {
        $this->_setAddressTypeId(Address::ADDRESS_TYPE_PARK);
    }
}