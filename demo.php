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
    $address = new Address();
    //inspecting the object
    echo '<h2>Empty object</h2>';
    echo '<tt><pre>'.var_export($address,true).'</pre></tt>';

//assigning values
    $address->countryName = 'Uganda';
    $address->subdivision = 'State';
    $address->cityName = 'Townsville';
    $address->streetAddress1 = '1251';
    $address->address_type_id = 1;
    $address->streetAddress2 = '9021';
    echo '<h2>Address object</h2>';
    echo '<tt><pre>'.var_export($address,true).'</pre></tt>';

//calling the dispaly method
    echo '<h2>Testing magic get and set</h2>';
    unset($address->postalCode);
    echo $address->display();

    echo '<h2>Testing __construct with an array</h2>';
    $address_2 = new Address(array(
        'countryName' => 'Uganda',
        'subdivision' => 'Region',
        'cityName' => 'Villageland',
        'streetAddress1' => '1251',
        'streetAddress2' => '265'

    ));

    echo $address_2->display();

    echo '<h2>Address2 __toString</h2>';
    echo $address_2;

    echo '<h2>Displaying address types</h2>';
    echo '<pre>'.var_export(Address::$validAddressTypes,true).'</pre>';

    echo '<h2>Testing validation of the address id</h2>';
    for ($id = 0; $id <= 4; $id++){
        echo '<div> '.$id. ':';
        echo Address::isValidAddressTypeId($id) ? 'Valid' : 'Invalid';
        echo '</div>';
    }
