import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;

public class b64hash {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java b64hash <input-string>");
            return;
        }

        String input = args[0];
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");

            // Compute the hash
            byte[] hash = digest.digest(input.getBytes(StandardCharsets.UTF_8));

            // Encode the hash to Base64
            String base64Hash = Base64.getEncoder().encodeToString(hash);
            System.out.println("Base64-encoded SHA-256 hash: " + base64Hash);
        } catch (NoSuchAlgorithmException e) {
            System.err.println("SHA-256 algorithm not found.");
        }
    }
}

