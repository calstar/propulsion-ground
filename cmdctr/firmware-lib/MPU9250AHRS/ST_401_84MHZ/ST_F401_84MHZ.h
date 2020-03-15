/* mbed library for the ST NUCLEO board F401RE 
 * to change the CPU clock to 84 MHz
 *
 * Copyright (c) 2014 Peter Drescher - DC2PD
 * Released under the MIT License: http://mbed.org/license/mit
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef MBED_ST_F401_84MHZ_H
#define MBED_ST_F401_84MHZ_H

/** Setup speed to 84 MHz
 *
 * @code
 * #include "mbed.h"
 * #include "ST_F401_84MHZ.h"
 *
 * // place the init before other code to ensure right timing of other objects !
 * F401_init84 myinit(0);   // use the internal oscillator 
 * 
 */

class F401_init84
{
public:
 /** Create a F401_init84 object to change the clock
   * @param external = 0 use internal oscillator
   * @param external = 1 use external 8 MHz crystal - you have to add some comonents to the pcb !
*/
F401_init84(unsigned int external);

protected:
// do the magic ;-)
void SystemClock_Config_84MHz_internal(void);   
void SystemClock_Config_84MHz_external(void);
};

#endif