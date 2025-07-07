## 1683. INVALID TWEETS

Write a solution to find the IDs of the invalid tweets.  
The tweet is invalid if the number of characters used in the content of the tweet is strictly greater than 15.

Return the result table in any order.

### Example 1:

**Input:**

**Tweets table:**

| tweet_id | content                           |
|----------|------------------------------------|
| 1        | Let us Code                        |
| 2        | More than fifteen chars are here! |

**Output:**

| tweet_id |
|----------|
| 2        |

**Explanation:**  
Tweet 1 has length = 11. It is a valid tweet.  
Tweet 2 has length = 33. It is an invalid tweet.

```sql
SELECT tweet_id FROM Tweets WHERE LENGTH(content) > 15;
```

---

## ARTICLE VIEWS

Write a solution to find all the authors that viewed at least one of their own articles.  
Return the result table sorted by id in ascending order.

### Example 1:

**Input:**

**Views table:**

| article_id | author_id | viewer_id | view_date  |
|------------|-----------|-----------|------------|
| 1          | 3         | 5         | 2019-08-01 |
| 1          | 3         | 6         | 2019-08-02 |
| 2          | 7         | 7         | 2019-08-01 |
| 2          | 7         | 6         | 2019-08-02 |
| 4          | 7         | 1         | 2019-07-22 |
| 3          | 4         | 4         | 2019-07-21 |
| 3          | 4         | 4         | 2019-07-21 |

**Output:**

| id |
|----|
| 4  |
| 7  |

```sql
SELECT DISTINCT author_id AS id 
FROM Views 
WHERE author_id = viewer_id 
ORDER BY id;
```

---

## 1757. LOW FATS AND RECYCLABLE

Write a solution to find the ids of products that are both low fat and recyclable.  
Return the result table in any order.

### Example 1:

**Input:**

**Products table:**

| product_id | low_fats | recyclable |
|------------|----------|------------|
| 0          | Y        | N          |
| 1          | Y        | Y          |
| 2          | N        | Y          |
| 3          | Y        | Y          |
| 4          | N        | N          |

**Output:**

| product_id |
|------------|
| 1
