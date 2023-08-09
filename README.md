# University Placement Information System with C99

It is a program that receives data from the user about the placement order of each student studying in the department in the university entrance exam (integer between 0-40000, entering 0 will mean that the data entry is over), department preference order (integer between 1-24), high school graduation grade (real number between 0-100) and the type of high school graduated from (string). 

After all data entries are finished, the program finds and prints on the screen the percentages (%) of students graduating from each high school type and their high school graduation grade averages, as well as the distribution (numbers) of the students in the department according to their order of preference for the department and the 5 thousandths of the success ranks based on placement.
<br>
<div align = "center">
**Example Output**
<br>
| Graduated High School Type | Student Ratio | Average High School Grade |
|:--------------------------:|:-------------:|:-------------------------:|
|     Meslek High School     |     5.00 %    |           89.98           |
|     Anadolu High School    |    65.43 %    |           88.25           |
|   Imam Hatip High School   |     4.56 %    |           91.50           |
|  Acik Ogretim High School  |     2.50 %    |           96.00           |
|       Fen High School      |    13.25 %    |           90.99           |
|             ...            |      ...      |            ...            |
|             ...            |      ...      |            ...            |
<br>
<br>
| Preference Order |  P1 |  P2 |  P3 | ... |  P8 |
|:----------------:|:---:|:---:|:---:|:---:|:---:|
|         1        |  0  |  0  |  1  | ... | 123 |
|         2        |  0  |  0  |  0  | ... |  98 |
|         3        |  1  |  0  |  2  | ... |  55 |
|        ...       | ... | ... | ... | ... | ... |
|        ...       | ... | ... | ... | ... | ... |
|        24        |  2  |  5  |  19 | ... |  60 |
<br>
</div>
**NOTE: **To run the program, you just need to download the zip file from Releases and run the exe file in Console.
