# Induction-Y24

Make a fork of this repo and create a branch in the fork with the following name: `[firstname]_[lastname_initial]`  
Example: `atulya_s`

## Task 1

### OverTheWire: Bandit  

Complete levels 0 to 15 of the [Bandit wargame](http://overthewire.org/wargames/bandit/).

- Create a markdown file named `otw.md`.
- For each level (0 to 15), write a short 2–3 line explanation covering:
  - What the level asked for
  - How you solved it (commands, logic, etc.)

- Commit this file to your branch.

## Task 2
### Netflix Inventory Management

You got your dream job in **MAANG**. To give other employees a run for their money, you have to come up with an **OOPS-based content rental client**.

---

#### High-Level Overview

Create a Netflix-style inventory management system using Object-Oriented Programming (OOPS). The system should manage a collection of movies, TV shows, and users, allowing them to browse, rent, and return content.
NOTE: Your Program should retain its memory of whatever data has been fed by the user

---

#### Login and Account Creation

1. The system should be accessed via a **CLI (Command Line Interface)**.
2. It should have options for:
   - **User Login / Sign-Up**
   - **Admin Login**
3. Users choose their own username. The system should ensure **uniqueness of usernames**.

---

#### User Account Features

1. Browse content by **category** (Movies or TV Shows) or **genre**.
2. **Search** content by **title** or **genre**.
3. **Rent** movies or TV shows.
4. **Return** rented content.
5. View currently rented items along with:
   - **Date rented**
   - **Last date of return**
6. View **purchased** items.
7. Check total **charges due**.

---

####  Admin Account Features

1. **Add** new movies and TV shows.
2. **Remove** existing movies and TV shows.
3. **Check** charges due for any user.

---

#### Content Structure

##### Common Attributes:
- **Title**
- **Genre**
- **Rating**
- `is_rented`
- `is_purchased`

---

##### Movie:
- **Duration**
- **Rent cost**
- **Purchase cost**

---

##### TV Show:
- **Seasons**
- **Episodes per season**
- **Per season rent cost**
- **Per season purchase cost**
---

#### Submission

- Fork the GitHub repository.
- Create a new branch with your name:  
  Format — `[firstname]_[lastname_initial]` (e.g., `atulya_s`)
- Submit a **pull request** by:  
   **11:59:59 PM, 13th May 2025**
- For any doubts, open an issue on the main repo.
- The task should be contained in a directory structured as Task2/{[firstname]_[lastname_initial]}/
- Also your code should be written in C++
- Your Code should have a Dockerfile along with it and we should be able to run it through docker as well
---

#### Suggestions

- Do **not** use GPT or other AI tools as we might very well ask you to explain your code as well as your thought process.
- Use your **own logic** and write clean, structured code.
- If you think you can make the program with alternative methods like MongoDB or SQL then you are free to do so.(But then your code should still run inside docker satisfying all the requirements)
- Feel free to get **creative** with features, but stick to the core requirements.
- Hint: For storage think of each object as a file.
---
