<?php
/**
 * Created by PhpStorm.
 * User: John Kagga
 * Date: 8/2/2015
 * Time: 10:27 AM
 */


    /**
     * Residence Address
     * Class AddressResidence
     */
class AddressResidence extends Address {

    /**
     * Force extending classes to implement init method
     * Add function to the __construct method in Address class
     * @return mixed
     */
    protected function _init()
    {
        $this->_setAddressTypeId(Address::ADDRESS_TYPE_RESIDENCE);
    }
}