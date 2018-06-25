<?php

/*
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *
 *     Check test.php for example usage. 
 *
 * @license http://www.opensource.org/licenses/mit-license.html  MIT License
 * @author Max Lindqvist <max.lindqvist@aceiq.com>
 */


include(__DIR__ . "/nitro_auth.inc");
include(__DIR__ . "/methods/auth.inc");

date_default_timezone_set('UTC');
$timestamp = date('U');

$auth_cache = file_get_contents($tmpPath . "/nitro_authtoken.cache");
$auth_array = explode(",", $auth_cache);

if (($timestamp > ($auth_array[0] + 900))) {
    echo "Generating new auth token\n";
    $authToken = ns::login();
    file_put_contents($tmpPath . "/nitro_authtoken.cache", "$timestamp,$authToken");
} else {
    echo "Using cached auth token\n";
    $authToken = $auth_array[1];
}


foreach (glob(__DIR__ . "/methods/*.inc") as $filename)
{
    if ($filename != __DIR__ . "/methods/auth.inc" && __DIR__ . "/methods/auth.inc") {
        include $filename;
    }
}

?>
