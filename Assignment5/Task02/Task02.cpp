#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class ClaimError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class PackageError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

double approve(double billed, double cover) {
    if (billed < 0 || cover < 0)
        throw std::invalid_argument("negative amount");
    if (billed > cover)
        throw ClaimError("exceeds cover");
    return billed;
}

double settle(double billed, double cover) {
    try {
        return approve(billed, cover);
    } catch (const ClaimError& e) {
        std::cout << "audit: " << e.what() << '\n';
        throw; // Rethrow the same exception object.
    }
}

double packageRate(const std::string& code) {
    if (code == "CARDIAC") return 75000.0;
    if (code == "EYE") return 25000.0;
    throw PackageError("unknown package: " + code);
}

struct ResourceGuard {
    std::string label;
    explicit ResourceGuard(std::string value) : label(std::move(value)) {}
    ~ResourceGuard() { std::cout << "destroyed " << label << '\n'; }
};

int main() {
    const double cases[][2] = {{40000, 50000}, {60000, 50000}, {-1, 50000}};
    for (const auto& item : cases) {
        try {
            const double paid = settle(item[0], item[1]);
            std::cout << "approved " << paid << '\n';
        } catch (const ClaimError& e) {
            std::cout << "claim rejected: " << e.what() << '\n';
        } catch (const std::exception& e) {
            std::cout << "error: " << e.what() << '\n';
        }
    }

    try {
        std::cout << "package rate: " << packageRate("UNKNOWN") << '\n';
    } catch (const PackageError& e) {
        std::cout << "package rejected: " << e.what() << '\n';
    }

    try {
        const std::string invalidNumber = "patient-charge";
        const double value = std::stod(invalidNumber);
        std::cout << value << '\n';
    } catch (const std::invalid_argument& e) {
        std::cout << "number error: " << e.what() << '\n';
    }

    try {
        ResourceGuard guard("claim-resource");
        throw ClaimError("simulated processing failure");
    } catch (const std::exception& e) {
        std::cout << "top-level caught: " << e.what() << '\n';
    }

    try {
        // This impossible array length throws std::bad_array_new_length,
        // which is derived from std::bad_alloc; it does not request real RAM.
        std::unique_ptr<char[]> impossible(
            new char[std::numeric_limits<std::size_t>::max()]);
        (void)impossible;
    } catch (const std::bad_alloc& e) {
        std::cout << "allocation caught: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cout << "allocation-related error: " << e.what() << '\n';
    }

    // Predict-and-verify program from the assignment.
    std::cout << "\nPrediction program: ";
    auto validate = [](double amount) {
        if (amount < 0) throw std::invalid_argument("negative");
        if (amount > 1e6) throw std::out_of_range("too large");
        std::cout << "ok ";
    };
    auto process = [&validate](double amount) {
        try {
            validate(amount);
        } catch (const std::out_of_range& e) {
            std::cout << "[log " << e.what() << "] ";
            throw;
        }
    };
    for (double amount : {100.0, -5.0, 2e6}) {
        try {
            process(amount);
            std::cout << "done ";
        } catch (const std::exception& e) {
            std::cout << "caught " << e.what() << ' ';
        }
    }
    std::cout << '\n';
    return 0;
}
