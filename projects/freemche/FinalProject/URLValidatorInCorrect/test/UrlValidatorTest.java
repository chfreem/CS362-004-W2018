

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   System.out.print("Running manual tests on isValid()\n");
	   UrlValidator urlVal = new UrlValidator(null, null,  UrlValidator.ALLOW_ALL_SCHEMES);
	   String[] arrayOfManualTests = {"http://www.google.com",
			   							"http://ww.go6ogle.com",
			   							"http://eecs.oregonstate.edu/online-cs-students",
			   							"https://www.wellsfargo.com/"};
	   boolean result;
	   for (int i=0; i<arrayOfManualTests.length; i++)
	   {
		   System.out.printf("i = %d, arrayOfManualTests[i] = %s\n", i, arrayOfManualTests[i]);
		   result = urlVal.isValid(arrayOfManualTests[i]);
		   if (result)
		   {
			   	System.out.printf("%s is a valid url\n", arrayOfManualTests[i]);
		   }
		   else
		   {
			   System.out.printf("%s is NOT a valid url\n", arrayOfManualTests[i]);
		   }
	   }
   } 
   
     
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
