# php-nitro
PHP library for Citrix NetScaler managament.

I finally decided to start the work on a PHP library for the most basic Citrix NetScaler tasks using the Nitro API.

The whole idea is to keep it simple. 
 - One config file
 - One inlude file
 - A common way to call all methods.
 
All classes corresponds to the same calls in the Nitro API to make it easy to use and extend. Every class has it's own file to make it easy to see which methods that has been implemented.

Every class has three methods:
 - check
 - add
 - rm

Check is used to check if the resource already exists.
Add is used to add configuration.
Rm is used to remote configuration.

There is now check if a resource already exists when you add or remove configuration. That, you will have to take care of using the check method (if you like to).

To start using the library, configure NetScaler IP, user, password and a writable temp path in nitro_auth.inc and include the nitro.inc.
The temp path is used to cache the auth token to minimize NetScaler logon requests.

Show test.php for sample usage.
