package safar.ws;

import javax.jws.WebService;

@WebService(name="BookService", serviceName="BookService")

public interface BookService {

    String getBook(Long id) ;
}