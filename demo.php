<?php
/**
 * Created by PhpStorm.
 * User: John Kagga
 * Date: 8/1/2015
 * Time: 12:53 PM
 */
require 'Address.inc';

    echo '<h2>Instantiating Address</h2>';
    $address = new Address();
    //inspecting the object
    echo '<h2>Empty object</h2>';
    echo '<tt><pre>'.var_export($address).'</pre></tt>';

//assigning values
    $address->countryName = 'Uganda';
    $address->postalCode = '256';
    $address->subdivision = 'Mengo';
    $address->cityName = 'Kampala';
    $address->streetAddress1 = '1251';
    $address->streetAddress2 = '9021';
    echo '<h2>Address object</h2>';
    echo '<tt><pre>'.var_export($address).'</pre></tt>';

//calling the dispaly method
    echo '<h2>Testing magic get and set</h2>';
    unset($address->postalCode);
    echo $address->display();

    echo '<h2>Testing __construct with an array</h2>';
    $address_2 = new Address(array(
        'countryName' => 'Uganda',
        'postalCode'=> '256',
        'subdivision' => 'Mengo',
        'cityName' => 'Kampala',
        'streetAddress1' => '1251',
        'streetAddress2' => '265'

    ));

    echo $address_2->display();

    echo '<h2>Address2 __toString</h2>';
    echo $address_2;
