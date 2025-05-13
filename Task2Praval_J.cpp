#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
//Abstract class for content
class Content {
public:
    std::string title;
    std::string genre;
    double rating;
    bool is_rented;

    Content(std::string t, std::string g, double r) : title(t), genre(g), rating(r), is_rented(false) {}
    virtual ~Content() {}
    virtual double getRentCost() const = 0;
    virtual double getPurchaseCost() const = 0;
    virtual std::string toString() const = 0;
};
// Derived classes for Movie
class Movie : public Content {
public:
    int duration;
    double rent_cost;
    double purchase_cost;

    Movie(std::string t, std::string g, double r, int d, double rc, double pc)
        : Content(t, g, r), duration(d), rent_cost(rc), purchase_cost(pc) {}

    double getRentCost() const override { return rent_cost; }
    double getPurchaseCost() const override { return purchase_cost; }
    std::string toString() const override {
        return "Movie|" + title + "|" + genre + "|" + std::to_string(rating) + "|" +
               std::to_string(duration) + "|" + std::to_string(rent_cost) + "|" + std::to_string(purchase_cost);
    }
};
// Derived classes for TVShow
class TVShow : public Content {
public:
    int seasons;
    int episodes_per_season;
    double rent_cost_per_season;
    double purchase_cost_per_season;

    TVShow(std::string t, std::string g, double r, int s, int eps, double rcps, double pcps)
        : Content(t, g, r), seasons(s), episodes_per_season(eps), rent_cost_per_season(rcps), purchase_cost_per_season(pcps) {}

    double getRentCost() const override { return rent_cost_per_season; }
    double getPurchaseCost() const override { return purchase_cost_per_season; }
    std::string toString() const override {
        return "TVShow|" + title + "|" + genre + "|" + std::to_string(rating) + "|" +
               std::to_string(seasons) + "|" + std::to_string(episodes_per_season) + "|" +
               std::to_string(rent_cost_per_season) + "|" + std::to_string(purchase_cost_per_season);
    }
};
// Rental class
class Rental {
public:
    Content* content;
    int season; // 0 if not applicable like for movies
    std::string rent_date;
    std::string due_date;
//Hardcoded dates for simplicity
    Rental(Content* c, int s = 0) : content(c), season(s), rent_date("2023-10-01"), due_date("2023-10-08") { 
        c->is_rented = true;
    }
    std::string toString() const {
        return content->title + "|" + std::to_string(season) + "|" + rent_date + "|" + due_date;
    }
};
// Purchase class
class Purchase {
public:
    Content* content;
    int season; // 0 if not applicable like for movies
    Purchase(Content* c, int s = 0) : content(c), season(s) {}
    std::string toString() const {
        return content->title + "|" + std::to_string(season);
    }
};
// User class
class User {
public:
    std::string username;
    std::vector<Rental> rented_items;
    std::vector<Purchase> purchased_items;

    User(std::string u) : username(u) {}

    bool isRented(Content* c, int season) const {
        return std::any_of(rented_items.begin(), rented_items.end(),
            [&](const Rental& r) { return r.content == c && r.season == season; });
    }

    bool isPurchased(Content* c, int season) const {
        return std::any_of(purchased_items.begin(), purchased_items.end(),
            [&](const Purchase& p) { return p.content == c && p.season == season; });
    }

    void rentContent(Content* c, int season = 0) {
        if (!isRented(c, season) && !isPurchased(c, season)) {
            rented_items.emplace_back(c, season);
        }
    }

    void returnContent(int index) {
        if (index >= 0 && index < rented_items.size()) {
            rented_items[index].content->is_rented = false;
            rented_items.erase(rented_items.begin() + index);
        }
    }

    void purchaseContent(Content* c, int season = 0) {
        if (!isPurchased(c, season)) {
            purchased_items.emplace_back(c, season);
        }
    }

    double checkCharges() const {
        double total = 0.0;
        for (const auto& r : rented_items) {
            total += r.content->getRentCost();
        }
        return total;
    }
};
// NetflixSystem class
class NetflixSystem {
private:
    std::vector<Content*> content_library;
    std::map<std::string, Content*> content_map;
    std::vector<User> users;
    User* current_user;
    bool is_admin;
    std::string content_file = "content.txt";
    std::string users_file = "users.txt";

public:
    NetflixSystem() : current_user(nullptr), is_admin(false) {
        loadData();
    }

    ~NetflixSystem() {
        saveData();
        for (auto c : content_library) delete c;
    }

    void run() {
        while (true) {
            if (is_admin) {
                adminMenu();
            } else if (current_user) {
                userMenu();
            } else {
                login();
            }
        }
    }

private:
    void loadData() {
        std::ifstream content_in(content_file);
        if (content_in.is_open()) {
            std::string line;
            while (std::getline(content_in, line)) {
                std::istringstream iss(line);
                std::string type;
                std::getline(iss, type, '|');
                if (type == "Movie") {
                    std::string title, genre, rating_str, duration_str, rent_cost_str, purchase_cost_str;
                    std::getline(iss, title, '|');
                    std::getline(iss, genre, '|');
                    std::getline(iss, rating_str, '|');
                    std::getline(iss, duration_str, '|');
                    std::getline(iss, rent_cost_str, '|');
                    std::getline(iss, purchase_cost_str, '|');
                    double rating = std::stod(rating_str);
                    int duration = std::stoi(duration_str);
                    double rent_cost = std::stod(rent_cost_str);
                    double purchase_cost = std::stod(purchase_cost_str);
                    Movie* m = new Movie(title, genre, rating, duration, rent_cost, purchase_cost);
                    content_library.push_back(m);
                    content_map[title] = m;
                } else if (type == "TVShow") {
                    std::string title, genre, rating_str, seasons_str, eps_str, rcps_str, pcps_str;
                    std::getline(iss, title, '|');
                    std::getline(iss, genre, '|');
                    std::getline(iss, rating_str, '|');
                    std::getline(iss, seasons_str, '|');
                    std::getline(iss, eps_str, '|');
                    std::getline(iss, rcps_str, '|');
                    std::getline(iss, pcps_str, '|');
                    double rating = std::stod(rating_str);
                    int seasons = std::stoi(seasons_str);
                    int eps = std::stoi(eps_str);
                    double rcps = std::stod(rcps_str);
                    double pcps = std::stod(pcps_str);
                    TVShow* t = new TVShow(title, genre, rating, seasons, eps, rcps, pcps);
                    content_library.push_back(t);
                    content_map[title] = t;
                }
            }
            content_in.close();
        }

        std::ifstream users_in(users_file);
        if (users_in.is_open()) {
            std::string line;
            while (std::getline(users_in, line)) {
                if (line == "END_USER") continue;
                User u(line);
                std::getline(users_in, line); // "Rented:"
                while (std::getline(users_in, line) && line != "Purchased:") {
                    std::istringstream iss(line);
                    std::string title, season_str, rent_date, due_date;
                    std::getline(iss, title, '|');
                    std::getline(iss, season_str, '|');
                    std::getline(iss, rent_date, '|');
                    std::getline(iss, due_date, '|');
                    int season = std::stoi(season_str);
                    if (content_map.count(title)) {
                        Rental r(content_map[title], season);
                        r.rent_date = rent_date;
                        r.due_date = due_date;
                        u.rented_items.push_back(r);
                    }
                }
                while (std::getline(users_in, line) && line != "END_USER") {
                    std::istringstream iss(line);
                    std::string title, season_str;
                    std::getline(iss, title, '|');
                    std::getline(iss, season_str, '|');
                    int season = std::stoi(season_str);
                    if (content_map.count(title)) {
                        u.purchased_items.emplace_back(content_map[title], season);
                    }
                }
                users.push_back(u);
            }
            users_in.close();
        }
    }

    void saveData() {
        std::ofstream content_out(content_file);
        for (const auto& c : content_library) {
            content_out << c->toString() << std::endl;
        }
        content_out.close();

        std::ofstream users_out(users_file);
        for (const auto& u : users) {
            users_out << u.username << std::endl;
            users_out << "Rented:" << std::endl;
            for (const auto& r : u.rented_items) {
                users_out << r.toString() << std::endl;
            }
            users_out << "Purchased:" << std::endl;
            for (const auto& p : u.purchased_items) {
                users_out << p.toString() << std::endl;
            }
            users_out << "END_USER" << std::endl;
        }
        users_out.close();
        
    }
    
    void login() {
    char choice;
    std::cout << "Do you want to login or signup? (l/s): ";
    std::cin >> choice;
    if (choice == 'l') {
        std::string username;
        std::cout << "Enter username: ";
        std::cin >> username;
        if (username == "admin") {
            std::string password;
            std::cout << "Enter admin password: ";
            std::cin >> password;
            if (password == "adminpass") {
                is_admin = true;
                std::cout << "Admin logged in.\n";
            } else {
                std::cout << "Incorrect password.\n";
            }
        } else {
            auto it = std::find_if(users.begin(), users.end(), [&](const User& u) { return u.username == username; });
            if (it != users.end()) {
                current_user = &(*it);
                std::cout << "User " << username << " logged in.\n";
            } else {
                std::cout << "Username not found.\n";
            }
        }
    } else if (choice == 's') {
        signup();
    } else {
        std::cout << "Invalid choice.\n";
    }
}

void signup() {
    std::string username;
    while (true) {
        std::cout << "Choose a username: ";
        std::cin >> username;
        if (username == "admin") {
            std::cout << "Username 'admin' is reserved. Please choose a different one.\n";
        } else if (std::any_of(users.begin(), users.end(), [&](const User& u) { return u.username == username; })) {
            std::cout << "Username already taken. Please choose a different one.\n";
        } else {
            users.emplace_back(username);
            current_user = &users.back();
            std::cout << "User " << username << " created and logged in.\n";
            break;
        }
    }
}
    void userMenu() {
        std::cout << "\nUser Menu:\n1. Browse\n2. Search\n3. Rent\n4. Return\n5. View Rented\n6. View Purchased\n7. Check Charges\n8. Logout\nChoice: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: browseContent(); break;
            case 2: searchContent(); break;
            case 3: rentContent(); break;
            case 4: returnContent(); break;
            case 5: viewRented(); break;
            case 6: viewPurchased(); break;
            case 7: checkCharges(); break;
            case 8: current_user = nullptr; std::cout << "Logged out.\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    }

    void adminMenu() {
        std::cout << "\nAdmin Menu:\n1. Add Content\n2. Remove Content\n3. Check User Charges\n4. Logout\nChoice: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: addContent(); break;
            case 2: removeContent(); break;
            case 3: checkUserCharges(); break;
            case 4: is_admin = false; std::cout << "Logged out.\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    }

    void browseContent() {
        std::string category;
        std::cout << "Browse movies or TV shows? (m/t): ";
        std::cin >> category;
        std::vector<Content*> list;
        if (category == "m") {
            for (auto c : content_library) {
                if (dynamic_cast<Movie*>(c)) list.push_back(c);
            }
        } else if (category == "t") {
            for (auto c : content_library) {
                if (dynamic_cast<TVShow*>(c)) list.push_back(c);
            }
        } else {
            std::cout << "Invalid choice.\n";
            return;
        }
        std::string genre;
        std::cout << "Enter genre (or blank for all): ";
        std::cin.ignore();
        std::getline(std::cin, genre);
        if (!genre.empty()) {
            list.erase(std::remove_if(list.begin(), list.end(), [&](Content* c) { return c->genre != genre; }), list.end());
        }
        for (size_t i = 0; i < list.size(); ++i) {
            std::cout << i + 1 << ". " << list[i]->title << " (" << list[i]->genre << ", Rating: " << list[i]->rating << ")\n";
        }
    }

    void searchContent() {
        std::string query;
        std::cout << "Enter title or genre: ";
        std::cin.ignore();
        std::getline(std::cin, query);
        for (const auto& c : content_library) {
            if (c->title.find(query) != std::string::npos || c->genre.find(query) != std::string::npos) {
                std::cout << c->title << " (" << c->genre << ", Rating: " << c->rating << ")\n";
            }
        }
    }

    void rentContent() {
        std::string title;
        std::cout << "Enter title to rent: ";
        std::cin.ignore();
        std::getline(std::cin, title);
        auto it = content_map.find(title);
        if (it == content_map.end()) {
            std::cout << "Content not found.\n";
            return;
        }
        Content* c = it->second;
        int season = 0;
        if (dynamic_cast<TVShow*>(c)) {
            std::cout << "Enter season (1-" << dynamic_cast<TVShow*>(c)->seasons << "): ";
            std::cin >> season;
        }
        if (current_user->isRented(c, season)) {
            std::cout << "Already rented.\n";
        } else if (current_user->isPurchased(c, season)) {
            std::cout << "Already purchased.\n";
        } else {
            current_user->rentContent(c, season);
            std::cout << "Rented " << title << (season ? " season " + std::to_string(season) : "") << "\n";
        }
    }

    void returnContent() {
        viewRented();
        std::cout << "Enter number to return: ";
        int index;
        std::cin >> index;
        current_user->returnContent(index - 1);
        std::cout << "Content returned.\n";
    }

    void viewRented() {
        for (size_t i = 0; i < current_user->rented_items.size(); ++i) {
            std::cout << i + 1 << ". " << current_user->rented_items[i].content->title
                      << (current_user->rented_items[i].season ? " S" + std::to_string(current_user->rented_items[i].season) : "")
                      << " (Due: " << current_user->rented_items[i].due_date << ")\n";
        }
    }

    void viewPurchased() {
        for (size_t i = 0; i < current_user->purchased_items.size(); ++i) {
            std::cout << i + 1 << ". " << current_user->purchased_items[i].content->title
                      << (current_user->purchased_items[i].season ? " S" + std::to_string(current_user->purchased_items[i].season) : "") << "\n";
        }
    }

    void checkCharges() {
        std::cout << "Total charges due: $" << current_user->checkCharges() << "\n";
    }

    void addContent() {
        std::string type;
        std::cout << "Add movie or TV show? (m/t): ";
        std::cin >> type;
        std::string title, genre;
        double rating;
        std::cout << "Title: ";
        std::cin.ignore();
        std::getline(std::cin, title);
        std::cout << "Genre: ";
        std::getline(std::cin, genre);
        std::cout << "Rating (0-10): ";
        std::cin >> rating;
        if (type == "m") {
            int duration;
            double rent_cost, purchase_cost;
            std::cout << "Duration (minutes): ";
            std::cin >> duration;
            std::cout << "Rent cost: ";
            std::cin >> rent_cost;
            std::cout << "Purchase cost: ";
            std::cin >> purchase_cost;
            Movie* m = new Movie(title, genre, rating, duration, rent_cost, purchase_cost);
            content_library.push_back(m);
            content_map[title] = m;
            std::cout << "Movie added.\n";
        } else if (type == "t") {
            int seasons, eps;
            double rcps, pcps;
            std::cout << "Number of seasons: ";
            std::cin >> seasons;
            std::cout << "Episodes per season: ";
            std::cin >> eps;
            std::cout << "Rent cost per season: ";
            std::cin >> rcps;
            std::cout << "Purchase cost per season: ";
            std::cin >> pcps;
            TVShow* t = new TVShow(title, genre, rating, seasons, eps, rcps, pcps);
            content_library.push_back(t);
            content_map[title] = t;
            std::cout << "TV Show added.\n";
        }
    }

    void removeContent() {
        std::string title;
        std::cout << "Enter title to remove: ";
        std::cin.ignore();
        std::getline(std::cin, title);
        auto it = content_map.find(title);
        if (it != content_map.end()) {
            content_library.erase(std::remove(content_library.begin(), content_library.end(), it->second), content_library.end());
            delete it->second;
            content_map.erase(it);
            std::cout << "Content removed.\n";
        } else {
            std::cout << "Content not found.\n";
        }
    }

    void checkUserCharges() {
        std::string username;
        std::cout << "Enter username: ";
        std::cin >> username;
        auto it = std::find_if(users.begin(), users.end(), [&](const User& u) { return u.username == username; });
        if (it != users.end()) {
            std::cout << "Charges for " << username << ": $" << it->checkCharges() << "\n";
        } else {
            std::cout << "User not found.\n";
        }
    }
};

int main() {
    NetflixSystem system;
    system.run();
    return 0;
}
