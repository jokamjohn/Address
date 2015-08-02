<?php
/**
 * Created by PhpStorm.
 * User: John Kagga
 * Date: 8/1/2015
 * Time: 12:53 PM
 */

    /**
     * Define auto-loader
     * @param string $className
     */
    function __autoload($className){
        include 'class.'.$className.'.inc';
    }

    echo '<h2>Instantiating Address</h2>';
    $addressResidence = new AddressResidence();
    //inspecting the object
    echo '<h2>Empty object</h2>';
    echo '<tt><pre>'.var_export($addressResidence,true).'</pre></tt>';

//assigning values
    $addressResidence->countryName = 'Uganda';
    $addressResidence->subdivision = 'State';
    $addressResidence->cityName = 'Townsville';
    $addressResidence->streetAddress1 = '1251';
    $addressResidence->address_type_id = 1;
    $addressResidence->streetAddress2 = '9021';
    echo '<h2>Address object</h2>';
    echo '<tt><pre>'.var_export($addressResidence,true).'</pre></tt>';

//calling the dispaly method
    echo '<h2>Testing magic get and set</h2>';
    unset($addressResidence->postalCode);
    echo $addressResidence->display();

    echo '<h2>Testing __construct with an array</h2>';
    $addressBusiness = new AddressBusiness(array(
        'countryName' => 'Uganda',
        'subdivision' => 'Region',
        'cityName' => 'Villageland',
        'streetAddress1' => '1251',
        'streetAddress2' => '265'

    ));

    echo $addressBusiness->display();
    echo '<h2>Debugging AddressBusiness</h2>';
    echo '<tt><pre>'.var_export($addressBusiness,true).'</pre></tt>';

    echo '<h2>Address2 __toString</h2>';
    echo $addressBusiness;


    echo '<h2>Displaying address types</h2>';
    echo '<pre>'.var_export(Address::$validAddressTypes,true).'</pre>';

    echo '<h2>Testing validation of the address id</h2>';
    for ($id = 0; $id <= 4; $id++){
        echo '<div> '.$id. ':';
        echo Address::isValidAddressTypeId($id) ? 'Valid' : 'Invalid';
        echo '</div>';
    }
